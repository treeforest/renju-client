#ifndef __MESSAGE_H__
#define __MESSAGE_H__

// 数据包格式
class Message 
{
public:
	// 消息体长度
	unsigned int msgLen;

	// 消息ID
	unsigned int msgID;
	
	// 消息体
	char data[];

	// 获取消息长度字节数
	const int GetMsgLenBinaryCnt() const { return 4; }

	// 获取消息ID字节数
	const int GetMsgIDBinaryCnt() const { return 4; }
};

#endif //！ __MESSAGE_H__