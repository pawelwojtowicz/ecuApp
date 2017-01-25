#include "CGSMDaemonStub.h"
#include <Runtime/CMessenger.h>
#include <Runtime/CMessage.h>
#include "GSMDaemonInterfaceConst.h"
#include "IGSMDaemonService.h"

namespace GSMDaemon
{
CGSMDaemonStub::CGSMDaemonStub(Runtime::IMessenger& rMessenger)
: Runtime::CStubBase(rMessenger, s_GSMDaemonQueueName)
, m_pGSMDaemonService(0)
{
}

CGSMDaemonStub::~CGSMDaemonStub()
{
}

bool CGSMDaemonStub::Initialize(IGSMDaemonService* pService)
{
	bool retVal(Runtime::CStubBase::Initialize());
	

	m_pGSMDaemonService = pService;

	SubscribeMessage(msgId_GSM_NotifyResponse);

	return retVal;
}

bool CGSMDaemonStub::Shutdown()
{
	bool retVal(Runtime::CStubBase::Shutdown());

	return retVal;
}

void CGSMDaemonStub::HandleMessage(Runtime::CMessage& rMessage)
{
	if ( 0 != m_pGSMDaemonService )
	{
		switch ( rMessage.GetMessageId() )
		{
		case msgId_GSM_NotifyResponse:
			{
				std::string response;
				bool ok = rMessage.GetValue(response);
	
				if (ok)
				{
					m_pGSMDaemonService->NotifyATResponseReceived(response);
				}
			};break;
		case msgId_GSM_NotifyAsyncResponse:
		{
			std::string response;
			bool ok = rMessage.GetValue(response);

			if (ok)
			{
				m_pGSMDaemonService->NotifyATPromptReceived(response);
			}
		};break;
		default:;
		};
	}
}



void CGSMDaemonStub::NotifyATResponseExtracted( const std::string line )
{
	Runtime::CMessage initDoneMsg(256);
	initDoneMsg.SetMessageId(msgId_GSM_NotifyResponse);
	initDoneMsg.SetMsgPrio(255);
	initDoneMsg.SetTargetId(OWN_QUEUE_ID);
	initDoneMsg.SetValue(line);

	GetMessenger().PostMessage(initDoneMsg);
}


void CGSMDaemonStub::NotifyATPromptExtracted( const std::string line )
{
	Runtime::CMessage initDoneMsg(256);
	initDoneMsg.SetMessageId(msgId_GSM_NotifyAsyncResponse);
	initDoneMsg.SetMsgPrio(255);
	initDoneMsg.SetTargetId(OWN_QUEUE_ID);
	initDoneMsg.SetValue(line);

	GetMessenger().PostMessage(initDoneMsg);
}


}
