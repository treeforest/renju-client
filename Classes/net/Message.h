#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <memory.h>
#include "crc32.h"

// 数据包格式
class Message 
{
public:
	// 消息体长度
	unsigned int dataLen;

	// 检验和
	unsigned int checksum;
	
	// 消息体
	char data[];

	static crc32 m_crc32;

	// 获取消息长度字节数
	const int MsgLenBytes() const { return 4; }

	// 获取检验和字节数
	const int ChecksumBytes() const { return 4; }

	// 获取消息头长度字节数
	const int MsgHeadBytes() const { return 8; }

	// Set
	void Set(unsigned int len, const char * data) {
		dataLen = len;
		memcpy(this->data, data, dataLen);
		checksum = m_crc32.ChecksumIEEE(data, dataLen);
	}

	// 校验和检测
	bool ChecksumIEEE() {
		if (checksum != m_crc32.ChecksumIEEE(data, dataLen)) {
			return false;
		}
		return true;
	}
};

#endif //！ __MESSAGE_H__