#ifndef RUNTIMECONST_H
#define RUNTIMECONST_H

#define MAX_MSG_SIZE 256
#define MAX_QUEUE_SIZE 10

typedef enum
{
	msgId_InvalidMsgId,
	msgId_Runtime_SubscribeMessage,
	msgId_Runtime_UnsubscribeMessage,
	msgId_Controller_TestMessage
} tMsgIds;

#endif
