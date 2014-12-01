#include "CControllerStub.h"
#include "ControllerInterfaceConst.h"
#include "IControllerServices.h"
#include "CPublicProcessInfo.h"
#include <Runtime/CMessenger.h>
#include <Runtime/CMessage.h>
#include <UCL/CSerializable.h>
#include <stdio.h>

namespace Controller
{
CControllerStub::CControllerStub(Runtime::IMessenger& rMessenger)
: Runtime::CStubBase(rMessenger, s_ControllerQueueName)
, m_sharedStorage(s_ControllerStorage, CPublicProcessInfo().GetStorageSize(),true)
{
}

CControllerStub::~CControllerStub()
{
}

bool CControllerStub::Initialize(IControllerServices* pControllerServices)
{
	bool retVal(Runtime::CStubBase::Initialize());
	
	retVal &= m_sharedStorage.Initialize();

	//attach the services
	m_pControllerServices = pControllerServices;

	SubscribeMessage(msgId_Controller_InitDone);
	SubscribeMessage(msgId_Controller_Heartbeat);
	SubscribeMessage(msgId_Controller_RestartRequest);
	SubscribeMessage(msgId_Controller_ShutdownRequest);

	return retVal;
}

bool CControllerStub::Shutdown()
{
	bool retVal(Runtime::CStubBase::Shutdown());

	return retVal;
}

void CControllerStub::HandleMessage(Runtime::CMessage& rMessage)
{
	if ( 0 != m_pControllerServices )
	{
		switch ( rMessage.GetMessageId() )
		{
		case msgId_Controller_InitDone:
			{
				UInt32 unitId(0);
				std::string versionInfo;
				std::string queueName;
				bool ok(false);
				ok = rMessage.GetValue(unitId);
			 	ok &= rMessage.GetValue(queueName);
				ok &= rMessage.GetValue(versionInfo);
	
				if (ok)
				{
					m_pControllerServices->NotifyUnitInitialized(unitId, queueName, versionInfo);
				}
			};break;
		case msgId_Controller_Heartbeat:
			{
				bool ok(false);
				UInt32 unitId(0);
				UInt8 unitStatus(0);
				ok = rMessage.GetValue(unitId);
			 	ok &= rMessage.GetValue(unitStatus);

				if (ok)
				{
					m_pControllerServices->NotifyUnitHeartbeat(	unitId, static_cast<tProcessStatus>(unitStatus));
				}
			};break;
		case msgId_Controller_RestartRequest:
			{
				m_pControllerServices->NotifyRestartRequest();
			};break;
		case msgId_Controller_ShutdownRequest:
			{
				m_pControllerServices->NotifyShutdownRequest();
			};break;
		default:;
		};
	}
	else
	{
		//no services available.
	}
}

bool CControllerStub::BroadcastPendingShutdown()
{
	Runtime::CMessage pendingShutdownMsg(256);
	pendingShutdownMsg.SetMessageId(msgId_Controller_PendingShutdown);
	pendingShutdownMsg.SetMsgPrio(255);
	pendingShutdownMsg.SetTargetId(BROADCAST_QUEUE_ID);

	return GetMessenger().PostMessage(pendingShutdownMsg);

}

bool CControllerStub::BroadcastShutdown()
{
	Runtime::CMessage shutdownMsg(256);
	shutdownMsg.SetMessageId(msgId_Controller_Shutdown);
	shutdownMsg.SetMsgPrio(255);
	shutdownMsg.SetTargetId(BROADCAST_QUEUE_ID);

	return GetMessenger().PostMessage(shutdownMsg);
}

bool CControllerStub::SendProcessStatus(const UInt32 processId, const tProcessStatus& status )
{
	UInt8 intStatus(static_cast<UInt8>(status));
	Runtime::CMessage initDoneMsg(256);
	initDoneMsg.SetMessageId(msgId_Controller_Heartbeat);
	initDoneMsg.SetMsgPrio(255);
	initDoneMsg.SetTargetId(OWN_QUEUE_ID);
	initDoneMsg.SetValue(processId);
	initDoneMsg.SetValue(intStatus);

	return GetMessenger().PostMessage(initDoneMsg);
}

bool CControllerStub::PublishProcessInfo( CPublicProcessInfo& processInfo)
{
	return m_sharedStorage.SetData(processInfo);
}

}
