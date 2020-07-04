#ifndef __ISEND_H__
#define __ISEND_H__
#include "Net.h"

/*
 * 连接后的相关操作
 */
class Connection {
public:
	static void Init(Net * net);
	static Connection * Instance();
	static void Clear();

	virtual void Send(unsigned int serviceID, unsigned int methodID, const char * data, unsigned int session = 0);

private:
	Connection(){}

private:
	static Connection * g_instance;
	static CRITICAL_SECTION g_cs;
	Net * m_net;
};

#endif
