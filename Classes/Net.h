
#ifndef __NET_H__
#define __NET_H__

#ifdef WIN32
#include <WinSock2.h>
#else
// in linux, android, ios

#endif

#include "Pool.h"
#include "Message.h"
#include <queue>
using namespace std;

/*
 * 客户端网络库
 */
class Net
{
public:

	static bool Connect(const char* ip, short port = 9999);
	static bool Start();

	static void Send(unsigned int msgLen, unsigned int serviceID, unsigned int methodID, char * data);
	static Message * Recv();

	static void Put(Message * msg);

	static bool Closed() { return m_closed; }// 判断当前网络是否关闭
	static void Close();

private:
	static bool StartRecv();
	static unsigned __stdcall WINAPI RecvThreadFunc(void* arg);
	static bool Recv(SOCKET s, char * buf, int len, int flags = 0);

	static bool StartSend();
	static unsigned __stdcall WINAPI SendThreadFunc(void* arg);

private:
	static SOCKET m_connetSocket;		// 客户端套接字
	static bool m_closed;				// 标记套接字状态
	static HANDLE m_hRecvHandle;		// 接收数据线程句柄
	static queue<Message*> m_recvQueue; // 存放接收的数据队列
	static HANDLE m_hSendHandle;		// 发送数据线程句柄
	static queue<Message*> m_sendQueue; // 存放发送的数据队列
	static Pool * m_msgPool;			// 消息临时对象池
};

#endif

