#include "CSubscriberMock.h"
#include <Runtime/CMessage.h>
#include "ISubscriberMockHelper.h"

namespace Runtime
{

CSubscriberMock::CSubscriberMock(ISubscriberMockHelper* pMockHelper)
: m_pMockHelper(pMockHelper)
{
}

CSubscriberMock::~CSubscriberMock()
{
}	

void CSubscriberMock::HandleMessage( CMessage& message )
{
	if ( 0 != m_pMockHelper )
	{
		tMsgIds msgId = message.GetMessageId();
		
		switch (msgId)
		{
			case msgId_Runtime_Timer_1000:
			{
				m_pMockHelper->TimerReceived();
			};break;
			default:;
		};

	}
}

}
