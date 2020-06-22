#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <memory.h>

// 数据包格式
class Message 
{
public:
	// 消息体长度
	unsigned int msgLen;

	// 访问的服务ID
	unsigned int serviceID;

	// 访问的服务里面的接口的ID
	unsigned int methodID;
	
	// 消息体
	char data[];

	// 获取消息长度字节数
	const int GetMsgLenBinaryCnt() const { return 4; }

	// 获取serviceID字节数
	const int GetServiceIDBinaryCnt() const { return 4; }

	// 获取methodID字节数
	const int GetMethodIDBinaryCnt() const { return 4; }

	// 获取消息头长度字节数
	const int GetMsgHeadBinaryCnt() const { return 12; }

	// GET
	const int GetMsgLen() { return msgLen; }
	const int GetServiceID() { return serviceID; }
	const int GetMethodID() { return methodID; }

	// SET
	void SetMsgLen(unsigned int msgLen) { this->msgLen = msgLen; }
	void SetServiceID(unsigned int serviceID) { this->serviceID = serviceID; }
	void SetMethodID(unsigned int methodID) { this->methodID = methodID; }
	void SetData(char * data) { memcpy(this->data, data, this->msgLen); }
};

#endif //！ __MESSAGE_H__