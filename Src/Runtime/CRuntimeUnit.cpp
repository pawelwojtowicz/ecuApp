#include "CRuntimeUnit.h"

namespace Runtime
{
CRuntimeUnit::CRuntimeUnit( const std::string& runtimeUnitName , const std::string& unitQueueName )
: CExecutable(runtimeUnitName)
, m_timerMessage(0)
, m_unitQueueName(unitQueueName)
, m_unitReturnValue(0)
{
	m_timerMessage.SetMessageId(msgId_Runtime_Timer_1000);
	m_timerMessage.SetMsgPrio(255);
	m_timerMessage.SetTargetId(OWN_QUEUE_ID);
}

CRuntimeUnit::~CRuntimeUnit()
{
}


void CRuntimeUnit::Initialize()
{
	m_messenger.Initialize(m_unitQueueName);
}

Int32 CRuntimeUnit::Run()
{
	m_messenger.StartMsgProcessor();
	return m_unitReturnValue;
}

void CRuntimeUnit::Shutdown()
{
	m_messenger.Shutdown();
}

void CRuntimeUnit::NotifyTimer()
{
	m_messenger.PostMessage(m_timerMessage);
}

void CRuntimeUnit::InitializeTimerManager()
{
	if ( m_messenger.SubscribeMessage( OWN_QUEUE_ID, msgId_Runtime_Timer_1000, &m_timerManager) )
	{
		InitializeTimer();
	}
}
}
