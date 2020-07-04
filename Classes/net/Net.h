
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
 * �ͻ��������
 */
class Net
{
public:

	static bool Connect(const char* ip, short port = 9999);
	static bool Start();

	static void Send(unsigned int msgLen, const char * data);
	static Message * Recv();

	static void Put(Message * msg);

	static bool Closed() { return m_closed; }// �жϵ�ǰ�����Ƿ�ر�
	static void Close();

private:
	static bool StartRecv();
	static unsigned __stdcall WINAPI RecvThreadFunc(void* arg);
	static bool Recv(SOCKET s, char * buf, int len, int flags = 0);

	static bool StartSend();
	static unsigned __stdcall WINAPI SendThreadFunc(void* arg);

private:
	static SOCKET m_connetSocket;		// �ͻ����׽���
	static bool m_closed;				// ����׽���״̬
	static HANDLE m_hRecvHandle;		// ���������߳̾��
	static queue<Message*> m_recvQueue; // ��Ž��յ����ݶ���
	static HANDLE m_hSendHandle;		// ���������߳̾��
	static queue<Message*> m_sendQueue; // ��ŷ��͵����ݶ���
	static Pool * m_msgPool;			// ��Ϣ��ʱ�����
};

#endif

