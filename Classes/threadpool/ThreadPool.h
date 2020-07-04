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

// 工作线程回调函数类型
typedef void(*ThreadPoolCallBack) (PARAM param);

/*
 * 线程状态
 */
enum TSTATUS
{
	// 被占用状态
	RUN,
	
	// 挂起状态
	SUSPENDED,
};

/*
 * 保存每个线程的信息
 */
struct stThreadInfo
{
	// 线程句柄
	HANDLE hHandle;
	
	// 线程ID				
	int id;
	
	// 线程状态						
	TSTATUS status;
	
	// 自定义的线程回调函数
	ThreadPoolCallBack func;
	
	// 线程参数		
	PARAM param;
};

/*
 * 保存线程要执行的内容信息
 */
struct stThreadExec
{
	// 线程执行的回调函数
	ThreadPoolCallBack func;

	// 回调函数的入参
	void * param;
};

/*
 * 优先级队列的相关信息（斐波那契堆）
 */
#define FIBHEAP_MIN_KEY 0// 斐波那契数列堆中的最小值
typedef int Key;
typedef stThreadExec* Value;
typedef FibHeapNode<Key, Value> PQNode;// 优先级队列节点
typedef int(*PriorityQueueCompare)(Key, Key);
int priority_queue_compare(Key k1, Key k2);

/*
 * 线程池
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
	// 关键段
	CRITICAL_SECTION m_cs;
	
	// 当前线程池句柄
	static ThreadPool* m_threadPool;

	// 空闲队列
	std::queue<PQNode*> m_freePQNode;
	std::queue<stThreadExec*> m_freeExec;
	
	// 优先级队列
	FibHeap<Key, Value, PriorityQueueCompare> * m_pPriQueue;

	// 线程池中最大线程数
	int m_maxThreadNum;

	// 保存每个线程的线程信息
	std::map<int, stThreadInfo*> m_threadInfoMap;

	// 线程池管理句柄
	HANDLE m_hThreadManager;
};

#endif //! __THREADPOOL_H__