#ifndef RUNTIMECONST_H
#define RUNTIMECONST_H

#define MAX_MSG_SIZE 256
#define MAX_QUEUE_SIZE 10

#define BROADCAST_QUEUE_ID 0
#define OWN_QUEUE_ID 1

typedef enum
{
	msgId_InvalidMsgId,
	msgId_Runtime_SubscribeMessage,
	msgId_Runtime_UnsubscribeMessage,
	msgId_Runtime_Timer_1000,
	msgId_Controller_InitDone,
	msgId_Controller_Heartbeat,
	msgId_Controller_RestartRequest,
	msgId_Controller_ShutdownRequest,
} tMsgIds;

#endif
