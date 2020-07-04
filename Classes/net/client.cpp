#include "client.h"
#include "Net.h"
#include "Connection.h"
#include "../threadpool/Lock.h"
#include <process.h>
#include <string>
using namespace std;

Client * Client::g_instance = NULL;

Client * Client::Instance()
{
	if (!g_instance) {
		CRITICAL_SECTION cs;
		InitializeCriticalSection(&cs);
		CLock * lock = new CLock(cs, "Instance");
		if (!g_instance) {
			g_instance = new Client();
		}
		delete lock;
		DeleteCriticalSection(&cs);
	}
	return g_instance;
}

/*
 * 启动客户端程序
 */
RetCode Client::Start(const char * ip, unsigned int port, _main_func_type mainFunc)
{
	m_ip = new char[strlen(ip) + 1]();
	memcpy(m_ip, ip, strlen(ip));
	m_port = port;

	// 1、初始化相关参数
	init();

	// 2、启动网络连接
	if (!m_net->Connect(ip, port)) {
		printf("Connect error\n");
		return RetCode::ERR_CONNECT;
	}
	if (!m_net->Start()) {
		printf("Start net error\n");
		return RetCode::ERR_NET_START;
	}

	printf("Connect Server[%s:%d] SUCC.\n", ip, port);

	// 3、初始化连接
	Connection::Init(m_net);

	// 4、主进程开始运行
	m_mainFunc = mainFunc;
	m_hMainHandle = (HANDLE)_beginthreadex(NULL, 0, mainFunc, NULL, 0, NULL);

	// 5、开始进行消息处理
	msg_handle();

	return RetCode::SUCCESS;
}

RetCode Client::Restart()
 {
	 return Start(m_ip, m_port, m_mainFunc);
 }

/*
 * 停止客户端程序，进行资源的释放
 */
void Client::Stop()
{
	clear();
}

/*
 * 注册路由，针对服务ID进行路由
 */
void Client::RegistryRouter(unsigned int serviceID, IRouter * obj)
{
	if (m_routeMap.count(serviceID) > 0) {
		printf("serviceID[%d] has existed\n", serviceID);
		return;
	}

	printf("registry router serviceID[%d] success...\n", serviceID);
	m_routeMap[serviceID] = obj;
}

void Client::init()
{
	m_net = new Net();
	if (m_net == NULL) {
		printf("m_net = new Net() error\n");
		abort();
	}

	m_threadPool = ThreadPool::CreateThreadPool(0);
}

void Client::clear()
{
	if (!m_net) {
		m_net->Close();
		delete m_net;
	}

	CloseHandle(m_hMainHandle);
}

void Client::msg_handle()
{
	Message * msg = NULL;

	while (1){
		// 1、获取收到的数据
		msg = m_net->Recv();
		if (msg == NULL) {
			Sleep(10);
			continue;
		}

		// 2、获取 Response
		Response * resp = new Response(m_net);
		resp->SetContext(msg->data, msg->dataLen);
		
		// 3、获取消息路由句柄
		if (m_routeMap.count(resp->GetServiceID()) < 1) {
			printf("can't find router with serviceID[%d]\n", resp->GetServiceID());
			continue;
		}

		// TODO: 临时对象池实现
		Task * task = new Task();
		task->route = m_routeMap[resp->GetServiceID()];
		task->resp = resp;

		// 4、将消息路由放入线程池中
		// TODO: 优先级处理
		m_threadPool->TrySubmitThreadpoolCallback(1, Client::MessageHandleCallBack, (void*)task);
	}
}

void Client::MessageHandleCallBack(PARAM param)
{
	Task * task = (Task*)param;
	task->route->PreHandle(task->resp);
	task->route->Handle(task->resp);
	task->route->PostHandle(task->resp);
	delete task;
}
