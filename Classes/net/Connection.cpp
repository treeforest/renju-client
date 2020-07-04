#include "Connection.h"
#include "../threadpool/Lock.h"
#include "../context/context.pb.h"

Connection * Connection::g_instance = NULL;
CRITICAL_SECTION Connection::g_cs;

void Connection::Init(Net * net)
{
	if (!g_instance) {
		CRITICAL_SECTION cs;
		InitializeCriticalSection(&cs);
		CLock * lock = new CLock(cs, "Init");
		if (!g_instance) {
			g_instance = new Connection();
			g_instance->m_net = net;
		}
		delete lock;
		DeleteCriticalSection(&cs);
	}
}

Connection * Connection::Instance()
{
	return g_instance;
}

void Connection::Clear()
{
	if (g_instance) {
		delete g_instance;
	}
}

/*
 * ·¢ËÍÊý¾Ý
 */
void Connection::Send(unsigned int serviceID, unsigned int methodID, const char * data, unsigned int session)
{
	string strMsg;
	Context ctx;
	ctx.set_session(session);
	ctx.set_serviceid(serviceID);
	ctx.set_methodid(methodID);
	ctx.set_data(data);
	ctx.SerializeToString(&strMsg);

	m_net->Send(strMsg.length(), strMsg.c_str());
}
