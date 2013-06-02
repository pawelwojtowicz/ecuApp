#ifndef RUNTIMECONST_H
#define RUNTIMECONST_H

static char s_BroadcastQueueName[] = {"/BroadcastQueue"};

typedef enum
{
	vMsgId_Heartbeat= 0x01,
	vMsgId_ShutdownRequest,
	vMsgId_PendingShutdown
} tMsgIds;

#endif
