#include "DataPack.h"
#include <string.h>

Message * DataPack::Pack(const char * data)
{
	if (data == NULL) {
		return NULL;
	}

	Message * msg = new Message();
	msg->msgLen = strlen(data);
	msg->msgID = 0;
	memcpy(msg->data, data, msg->msgLen);

	return msg;
}

Message * DataPack::Unpack(const char * buf)
{
	if (buf == NULL) {
		return NULL;
	}

	Message * msg = new Message();
	memcpy(msg, buf, strlen(buf));

	return msg;
}
