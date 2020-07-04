#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "IRouter.h"
#include "Net.h"
#include <map>

#include "../threadpool/ThreadPool.h"

// 错误码
enum class RetCode {
	SUCCESS = 0,
	ERR_CONNECT = 1,
	ERR_NET_START = 2
};

// 消息处理任务
struct Task {
	IRouter * route;
	Response * resp;
};

typedef unsigned int(_stdcall *_main_func_type)(void *);

class Client
{
public:
	static Client * Instance();
	RetCode Start(const char * ip, unsigned int port, _main_func_type mainFunc);
	RetCode Restart();
	void Stop();
	void RegistryRouter(unsigned int serviceID, IRouter * obj);
	
protected:
	Client() {}
	void init();
	void clear();
	void msg_handle();
	static void MessageHandleCallBack(PARAM param);

private:
	_main_func_type m_mainFunc;
	HANDLE m_hMainHandle;
	Net * m_net;
	std::map<unsigned int, IRouter*> m_routeMap;
	ThreadPool * m_threadPool;
	char * m_ip;
	unsigned int m_port;
	static Client * g_instance;
};

#endif //! __CLIENT_H__