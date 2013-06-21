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
	return true;
}

bool CControllerProxy::RequestShutdown()
{
	return true;
}

bool CControllerProxy::RequestRestart()
{
	return true;
}
}
