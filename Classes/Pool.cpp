#include "Pool.h"
#include "malloc.h"

Message * Pool::Get(unsigned int msgLen)
{
	Message * msg = NULL;

	if (m_free.empty()) {
		msg = (Message*)malloc(sizeof(char) * (msgLen + 8));
	}
	else {
		msg = m_free.front();
		m_free.pop();
		msg = (Message*)realloc(msg, sizeof(char) * (msgLen + 8));
	}

	return msg;
}

void Pool::Put(Message * msg)
{
	m_free.push(msg);
}

void Pool::Clear()
{
	Message * msg = NULL;
	while (!m_free.empty()){
		msg = m_free.front();
		free(msg);
		m_free.pop();
	}
}

