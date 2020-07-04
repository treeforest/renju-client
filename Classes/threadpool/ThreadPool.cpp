#include "ThreadPool.h"
#include <process.h>
#include "Lock.h"

ThreadPool * ThreadPool::m_threadPool;

/*
 * �����̳߳�
 *
 * ������
 *  maxNum: �̳߳�������߳�����Ĭ��Ϊ0���Զ������߳���Ϊ��ǰ��cpu�ĺ�����*2+2
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
 * ����ǰ��������������̳߳���
 *
 * ������
 *  priority: ���ȼ�����1��ʼ��1�����ȼ�����������μ���
 *  func�� �ص�����������ĺ���
 *  param���ص���������Ĳ�����Ϣ
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
 * �ر��̳߳�
 */
void ThreadPool::Stop()
{
	// �ؼ���
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
	// �ؼ���
	InitializeCriticalSection(&m_cs);

	// ���ȼ�����
	m_pPriQueue = new FibHeap<Key, Value, PriorityQueueCompare>(priority_queue_compare, FIBHEAP_MIN_KEY);
	if (!m_pPriQueue) {
		printf("init FibHeap error.");
		return;
	}

	// �̳߳�
	if (maxNum <= 0) {
		SYSTEM_INFO sysinfo;
		GetSystemInfo(&sysinfo);					// ��ȡ����ϵͳ��Ϣ
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

	// �̳߳ع����߳�
	m_hThreadManager = (HANDLE)_beginthreadex(NULL, 0, ThreadManager, NULL, 0, NULL);
}

/*
 * �̳߳����߳�ִ������
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
 * �̳߳ع����߳�ִ������
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
* ��ȡ��ǰ�̳߳�ʵ������
*/
ThreadPool * ThreadPool::GetThreadPool()
{
	return m_threadPool;
}

/*
 * ��������
 */
void ThreadPool::run(int nThreadID)
{
	if (m_threadInfoMap[nThreadID]->status == RUN) {
		m_threadInfoMap[nThreadID]->func(m_threadInfoMap[nThreadID]->param);
	}
}

/*
 * �����߳�
 */
void ThreadPool::suspend_thread(int nThreadID)
{
	m_threadInfoMap[nThreadID]->status = SUSPENDED;
	SuspendThread(m_threadInfoMap[nThreadID]->hHandle);
}

/*
 * ����������������������Ϣ������ȡ����Ȼ�����������̲߳���
 */
void ThreadPool::allocat_task()
{
	// 1��ȡ��������ȼ�������
	if (m_pPriQueue->Size() == 0) {
		return;
	}

	CLock * lock = new CLock(m_cs, "allocat_task");
	PQNode * node = m_pPriQueue->ExtractMin();
	delete lock;

	// 2�������������߳�
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

				// ������Դ(��ʱ����)
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
