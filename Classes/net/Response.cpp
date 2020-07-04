#include "Response.h"
#include <string>
using namespace std;

Response::Response(Net * net)
{
	m_net = net;
	m_ctx = new Context();
}

Response::~Response()
{
	if (m_ctx) {
		delete m_ctx;
	}
}

bool Response::SetContext(const char * data, int size)
{
	if (!m_ctx->ParseFromArray(data, size)) {
		printf("Failed to parse context.\n");
		return false;
	}

	return true;
}

void Response::Send(char * data)
{
	string strMsg;
	Context ctx = *m_ctx;
	ctx.set_data(data);
	ctx.SerializeToString(&strMsg);

	m_net->Send(strMsg.length(), strMsg.c_str());
}

unsigned int Response::GetServiceID()
{
	return m_ctx->serviceid();
}

unsigned int Response::GetMethodID()
{
	return m_ctx->methodid();
}

Context * Response::GetContext()
{
	return m_ctx;
}
