#include "CTTSStub.h"
#include "TTSInterfaceConst.h"
#include "ITTSServices.h"
#include <Runtime/CMessenger.h>
#include <Runtime/CMessage.h>
#include <UCL/CSerializable.h>
#include <stdio.h>

namespace TTS
{
CTTSStub::CTTSStub(Runtime::IMessenger& rMessenger)
: Runtime::CStubBase(rMessenger, s_TTSQueueName)
{
}

CTTSStub::~CTTSStub()
{
}

bool CTTSStub::Initialize(ITTSServices* pTTSServices)
{
	bool retVal(Runtime::CStubBase::Initialize());

	//attach the services
	m_pTTSServices = pTTSServices;

	SubscribeMessage(msgId_TTS_SayPhrase);

	return retVal;
}

bool CTTSStub::Shutdown()
{
	bool retVal(Runtime::CStubBase::Shutdown());

	return retVal;
}

void CTTSStub::HandleMessage(Runtime::CMessage& rMessage)
{
	if ( 0 != m_pTTSServices )
	{
		switch ( rMessage.GetMessageId() )
		{
		case msgId_TTS_SayPhrase:
			{
				std::string phrase;
	
				if (rMessage.GetValue(phrase))
				{
					m_pTTSServices->Say(phrase);
				}
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
