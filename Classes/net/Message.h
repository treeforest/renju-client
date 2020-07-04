#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <memory.h>
#include "crc32.h"

// ���ݰ���ʽ
class Message 
{
public:
	// ��Ϣ�峤��
	unsigned int dataLen;

	// �����
	unsigned int checksum;
	
	// ��Ϣ��
	char data[];

	static crc32 m_crc32;

	// ��ȡ��Ϣ�����ֽ���
	const int MsgLenBytes() const { return 4; }

	// ��ȡ������ֽ���
	const int ChecksumBytes() const { return 4; }

	// ��ȡ��Ϣͷ�����ֽ���
	const int MsgHeadBytes() const { return 8; }

	// Set
	void Set(unsigned int len, const char * data) {
		dataLen = len;
		memcpy(this->data, data, dataLen);
		checksum = m_crc32.ChecksumIEEE(data, dataLen);
	}

	// У��ͼ��
	bool ChecksumIEEE() {
		if (checksum != m_crc32.ChecksumIEEE(data, dataLen)) {
			return false;
		}
		return true;
	}
};

#endif //�� __MESSAGE_H__