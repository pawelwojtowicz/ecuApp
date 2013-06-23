#include "CControllerProxy.h"
#include <Runtime/IMessenger.h>
#include <Runtime/CMessage.h>
#include "IControllerListener.h"
#include "ControllerInterfaceConst.h"
#include <stdio.h>

namespace Controller
{
CControllerProxy::CControllerProxy(Runtime::IMessenger& rMessenger)
: Runtime::CProxyBase(rMessenger, s_ControllerQueueName)
, m_pControllerListener(0)
{
}

CControllerProxy::~CControllerProxy()
{
}

bool CControllerProxy::Initialize(IControllerListener* pListener)
{
	bool retVal(CProxyBase::Initialize());

	if ( 0 != pListener )
	{
		m_pControllerListener = pListener;
		retVal &= SubscribeMessage(msgId_Controller_PendingShutdown);
		retVal &= SubscribeMessage(msgId_Controller_Shutdown); 
	}
	else
	{
		retVal = false;
	}

	return retVal;
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
	Runtime::CMessage initDoneMsg(256);
	initDoneMsg.SetMessageId(msgId_Controller_RestartRequest);
	initDoneMsg.SetMsgPrio(255);
	initDoneMsg.SetTargetId(GetTargetQueueId());

	return GetMessenger().PostMessage(initDoneMsg);
}

void CControllerProxy::HandleMessage(Runtime::CMessage& rMessage)
{
	if (0 != m_pControllerListener)
	{
		switch ( rMessage.GetMessageId() )
		{
			case msgId_Controller_PendingShutdown:
			{
				m_pControllerListener->NotifyShutdownPending();
			};break;
			case msgId_Controller_Shutdown:
			{
				m_pControllerListener->ShutdownProcess();
			};break;
			default:;
		}
	}
}

}
