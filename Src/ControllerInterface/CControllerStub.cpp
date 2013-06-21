#include "CControllerStub.h"
#include "ControllerInterfaceConst.h"
#include "IControllerServices.h"
#include <Runtime/CMessenger.h>
#include <Runtime/CMessage.h>

namespace Controller
{
CControllerStub::CControllerStub(Runtime::IMessenger& rMessenger)
: Runtime::CStubBase(rMessenger, s_ControllerQueueName)
{
}

CControllerStub::~CControllerStub()
{
}

bool CControllerStub::Initialize(IControllerServices* pControllerServices)
{
	bool retVal(Runtime::CStubBase::Initialize());

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
			};break;
		case msgId_Controller_Heartbeat:
			{
			};break;
		case msgId_Controller_RestartRequest:
			{
			};break;
		case msgId_Controller_ShutdownRequest:
			{
			};break;
		default:;
		};
	}
	else
	{
		//no services available.
	}
}


}
