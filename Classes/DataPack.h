#ifndef __DATAPACK_H__
#define __DATAPACK_H__

#include "Message.h"

/*
 * 对信息的封包解包
 */
class DataPack
{
public:
	static Message * Pack(const char * data);
	static Message * Unpack(const char * buf);
};

#endif