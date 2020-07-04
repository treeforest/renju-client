#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <windows.h>
#include <string>
#include <queue>
#include <map>
#include "fibheap.hpp"

#ifndef __prame__
#define __prame__
typedef void* PARAM;
#endif //! __prame__

// �����̻߳ص���������
typedef void(*ThreadPoolCallBack) (PARAM param);

/*
 * �߳�״̬
 */
enum TSTATUS
{
	// ��ռ��״̬
	RUN,
	
	// ����״̬
	SUSPENDED,
};

/*
 * ����ÿ���̵߳���Ϣ
 */
struct stThreadInfo
{
	// �߳̾��
	HANDLE hHandle;
	
	// �߳�ID				
	int id;
	
	// �߳�״̬						
	TSTATUS status;
	
	// �Զ�����̻߳ص�����
	ThreadPoolCallBack func;
	
	// �̲߳���		
	PARAM param;
};

/*
 * �����߳�Ҫִ�е�������Ϣ
 */
struct stThreadExec
{
	// �߳�ִ�еĻص�����
	ThreadPoolCallBack func;

	// �ص����������
	void * param;
};

/*
 * ���ȼ����е������Ϣ��쳲������ѣ�
 */
#define FIBHEAP_MIN_KEY 0// 쳲��������ж��е���Сֵ
typedef int Key;
typedef stThreadExec* Value;
typedef FibHeapNode<Key, Value> PQNode;// ���ȼ����нڵ�
typedef int(*PriorityQueueCompare)(Key, Key);
int priority_queue_compare(Key k1, Key k2);

/*
 * �̳߳�
 */
class ThreadPool
{
public:
	static ThreadPool * CreateThreadPool(int maxNum = 0);
	void TrySubmitThreadpoolCallback(int priority, ThreadPoolCallBack func, void * param);
	void Stop();

private:
	ThreadPool() {}
	~ThreadPool() {}
	ThreadPool(int maxNum);

	static unsigned __stdcall ThreadFunc(void * param);
	static unsigned __stdcall ThreadManager(void * param);
	static ThreadPool * GetThreadPool();

	void run(int nThreadID);
	void suspend_thread(int nThreadID);
	void allocat_task();

	PQNode * GetNode();
	void PutNode(PQNode * node);
	stThreadExec * GetExec();
	void PutExec(stThreadExec * exec);

private:
	// �ؼ���
	CRITICAL_SECTION m_cs;
	
	// ��ǰ�̳߳ؾ��
	static ThreadPool* m_threadPool;

	// ���ж���
	std::queue<PQNode*> m_freePQNode;
	std::queue<stThreadExec*> m_freeExec;
	
	// ���ȼ�����
	FibHeap<Key, Value, PriorityQueueCompare> * m_pPriQueue;

	// �̳߳�������߳���
	int m_maxThreadNum;

	// ����ÿ���̵߳��߳���Ϣ
	std::map<int, stThreadInfo*> m_threadInfoMap;

	// �̳߳ع�����
	HANDLE m_hThreadManager;
};

#endif //! __THREADPOOL_H__