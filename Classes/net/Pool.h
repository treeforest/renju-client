#ifndef __POOL_H__
#define __POOL_H__

#include "Message.h"
#include <queue>
using namespace std;

// ∂‘œÛ≥ÿ
class Pool 
{
public:
	Message * Get(unsigned int msgLen);
	void Put(Message * msg);
	void Clear();

private:
	queue<Message*> m_free;
};

#endif // !__POOL_H__



