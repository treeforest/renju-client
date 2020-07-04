#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#ifdef _DEBUG 
#pragma comment(lib, "libprotobufd.lib")  
#pragma comment(lib, "libprotocd.lib")
#else
#pragma comment(lib, "libprotobuf.lib")  
#pragma comment(lib, "libprotoc.lib")
#endif

#include "../context/context.pb.h"
#include "Net.h"

class Response
{
public:
	Response(Net * net);
	~Response();
	bool SetContext(const char * data, int size);

	void Send(char * data);
	unsigned int GetServiceID();
	unsigned int GetMethodID();
	Context * GetContext();

private:
	Response() {}

private:
	Context * m_ctx;
	Net * m_net;
};

#endif