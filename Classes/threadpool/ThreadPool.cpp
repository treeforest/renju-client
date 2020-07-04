#include "ThreadPool.h"
#include <process.h>
#include "Lock.h"

ThreadPool * ThreadPool::m_threadPool;

/*
 * 创建线程池
 *
 * 参数：
 *  maxNum: 线程池中最大线程数，默认为0，自动分配线程数为当前：cpu的核心数*2+2
 */
ThreadPool * ThreadPool::CreateThreadPool(int maxNum)
{
	if (m_threadPool == NULL)
	{
		m_threadPool = new ThreadPool(maxNum);
	}
	return m_threadPool;
}

/*
 * 将当前待处理任务放入线程池中
 *
 * 参数：
 *  priority: 优先级。从1开始，1的优先级最大，往后依次减弱
 *  func： 回调函数（处理的函数
 *  param：回调函数处理的参数信息
 */
void ThreadPool::TrySubmitThreadpoolCallback(int priority, ThreadPoolCallBack func, void * param)
{
	if (priority <= FIBHEAP_MIN_KEY) {
		printf("ERROR: priority is less %d\n", FIBHEAP_MIN_KEY);
		return;
	}

	stThreadExec * pVal = GetExec();
	pVal->func = func;
	pVal->param = param;

	PQNode * node = GetNode();
	node->key = priority;
	node->val = pVal;

	CLock lock(m_cs, "PushTask");
	m_pPriQueue->Insert(node);
}

/*
 * 关闭线程池
 */
void ThreadPool::Stop()
{
	// 关键段
	DeleteCriticalSection(&m_cs);

	// m_freePQNode
	PQNode * pNode = NULL;
	while (!m_freePQNode.empty()) {
		pNode = m_freePQNode.front();
		m_freePQNode.pop();
		delete pNode;
	}
	pNode = NULL;

	// m_freeExec
	stThreadExec * pExec = NULL;
	while (!m_freeExec.empty()) {
		pExec = m_freeExec.front();
		m_freeExec.pop();
		delete pExec;
	}
	pExec = NULL;

	// m_pPriQueue
	PQNode * node = NULL;
	do 
	{
		node = m_pPriQueue->ExtractMin();
		if (!node) {
			break;
		}
		delete node;
	} while (1);
	node = NULL;
	delete m_pPriQueue;

	// m_hThreadManager
	CloseHandle(m_hThreadManager);

	// m_threadInfoMap
	std::map<int, stThreadInfo*>::iterator it;
	for (it = m_threadInfoMap.begin(); it != m_threadInfoMap.end(); ++it) {
		stThreadInfo * pInfo = it->second;
		CloseHandle(pInfo->hHandle);
		delete pInfo;
	}
	m_threadInfoMap.erase(m_threadInfoMap.begin(), m_threadInfoMap.end());
}

ThreadPool::ThreadPool(int maxNum)
{
	// 关键段
	InitializeCriticalSection(&m_cs);

	// 优先级队列
	m_pPriQueue = new FibHeap<Key, Value, PriorityQueueCompare>(priority_queue_compare, FIBHEAP_MIN_KEY);
	if (!m_pPriQueue) {
		printf("init FibHeap error.");
		return;
	}

	// 线程池
	if (maxNum <= 0) {
		SYSTEM_INFO sysinfo;
		GetSystemInfo(&sysinfo);					// 获取操作系统信息
		maxNum = sysinfo.dwNumberOfProcessors * 2 + 2;
	}
	m_maxThreadNum = maxNum;

	for (int i = 0; i < maxNum; i++) {
		HANDLE hHandle = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (void*)i, CREATE_SUSPENDED, NULL);
		stThreadInfo * pThreadInfo = new stThreadInfo();
		pThreadInfo->hHandle = hHandle;
		pThreadInfo->id = i;
		pThreadInfo->status = SUSPENDED;
		m_threadInfoMap[i] = pThreadInfo;
	}

	// 线程池管理线程
	m_hThreadManager = (HANDLE)_beginthreadex(NULL, 0, ThreadManager, NULL, 0, NULL);
}

/*
 * 线程池中线程执行主体
 */
unsigned ThreadPool::ThreadFunc(void * param)
{
	while (1) {
		ThreadPool::GetThreadPool()->run((int)param);
		ThreadPool::GetThreadPool()->suspend_thread((int)param);
	}
	return 0;
}

/*
 * 线程池管理线程执行主体
 */
unsigned ThreadPool::ThreadManager(void * param)
{
	while (1) {
		ThreadPool::GetThreadPool()->allocat_task();
		Sleep(10);
	}
	return 0;
}

/*
* 获取当前线程池实例对象
*/
ThreadPool * ThreadPool::GetThreadPool()
{
	return m_threadPool;
}

/*
 * 运行任务
 */
void ThreadPool::run(int nThreadID)
{
	if (m_threadInfoMap[nThreadID]->status == RUN) {
		m_threadInfoMap[nThreadID]->func(m_threadInfoMap[nThreadID]->param);
	}
}

/*
 * 挂起线程
 */
void ThreadPool::suspend_thread(int nThreadID)
{
	m_threadInfoMap[nThreadID]->status = SUSPENDED;
	SuspendThread(m_threadInfoMap[nThreadID]->hHandle);
}

/*
 * 分配任务操作：将任务从消息队列中取出，然后分配给空闲线程操作
 */
void ThreadPool::allocat_task()
{
	// 1、取出最大优先级的任务
	if (m_pPriQueue->Size() == 0) {
		return;
	}

	CLock * lock = new CLock(m_cs, "allocat_task");
	PQNode * node = m_pPriQueue->ExtractMin();
	delete lock;

	// 2、将任务分配给线程
	std::map<int, stThreadInfo*>::iterator it;
	while (1){
		for (it = m_threadInfoMap.begin(); it != m_threadInfoMap.end(); ++it)
		{
			if ((it->second)->status == SUSPENDED)
			{
				(it->second)->func = node->val->func;
				(it->second)->param = node->val->param;
				(it->second)->status = RUN;
				ResumeThread((it->second)->hHandle);

				// 回收资源(临时对象)
				PutExec(node->val);
				PutNode(node);
				return;
			}
		}
		Sleep(10);
	}
}

PQNode * ThreadPool::GetNode()
{
	PQNode * node = NULL;
	CLock lock(m_cs, "GetNode");
	if (m_freePQNode.empty()) {
		node = new PQNode();
	}
	else {
		node = m_freePQNode.front();
		m_freePQNode.empty();
		memset(node, 0, sizeof(PQNode));
	}
	return node;
}

void ThreadPool::PutNode(PQNode * node)
{
	m_freePQNode.push(node);
}

stThreadExec * ThreadPool::GetExec()
{
	stThreadExec * exec = NULL;
	CLock lock(m_cs, "GetExec");
	if (m_freeExec.empty()) {
		exec = new stThreadExec();
	}
	else {
		exec = m_freeExec.front();
		m_freeExec.pop();
		memset(exec, 0, sizeof(exec));
	}
	return exec;
}

void ThreadPool::PutExec(stThreadExec * exec)
{
	m_freeExec.push(exec);
}

int priority_queue_compare(Key k1, Key k2) {
	if (k1 == FIBHEAP_MIN_KEY) {
		return -1;
	}
	else if (k2 == FIBHEAP_MIN_KEY) {
		return 1;
	}
	return k1 - k2;
}
