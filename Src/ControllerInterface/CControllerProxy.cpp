#include "CControllerProxy.h"
#include <Runtime/IMessenger.h>
#include <Runtime/CMessage.h>
#include "ControllerInterfaceConst.h"

namespace Controller
{
CControllerProxy::CControllerProxy(Runtime::IMessenger& rMessenger)
: Runtime::CProxyBase(rMessenger, s_ControllerQueueName)
{
}

CControllerProxy::~CControllerProxy()
{
}

bool CControllerProxy::ReportInitDone(const UInt32& processId, const std::string& processQueue, const std::string& unitVersion)
{
	Runtime::CMessage initDoneMsg(256);
	initDoneMsg.SetMessageId(msgId_Controller_InitDone);
	initDoneMsg.SetMsgPrio(255);
	initDoneMsg.SetTargetId(GetTargetQueueId());
	initDoneMsg.SetValue(processId);
	initDoneMsg.SetValue(processQueue);
	initDoneMsg.SetValue(unitVersion);

	return GetMessenger().PostMessage(initDoneMsg);
}

bool CControllerProxy::SendProcessHeartbeat(const UInt32 processId, const tProcessStatus& status )
{
	UInt8 intStatus(static_cast<UInt8>(status));
	Runtime::CMessage initDoneMsg(256);
	initDoneMsg.SetMessageId(msgId_Controller_Heartbeat);
	initDoneMsg.SetMsgPrio(255);
	initDoneMsg.SetTargetId(GetTargetQueueId());
	initDoneMsg.SetValue(processId);
	initDoneMsg.SetValue(intStatus);

	return GetMessenger().PostMessage(initDoneMsg);
}

bool CControllerProxy::RequestShutdown()
{
	Runtime::CMessage initDoneMsg(256);
	initDoneMsg.SetMessageId(msgId_Controller_ShutdownRequest);
	initDoneMsg.SetMsgPrio(255);
	initDoneMsg.SetTargetId(GetTargetQueueId());

	return GetMessenger().PostMessage(initDoneMsg);
}

bool CControllerProxy::RequestRestart()
{
	return true;
}
}
