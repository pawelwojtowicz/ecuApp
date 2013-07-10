#include "CRuntimeUnit.h"
#include <cstdlib>

namespace Runtime
{
CRuntimeUnit::CRuntimeUnit( const std::string& runtimeUnitName , const std::string& unitQueueName )
: CExecutable(runtimeUnitName)
, m_controllerProxy(m_messenger)
, m_healthReporter(m_timerManager,m_controllerProxy)
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
	m_controllerProxy.Initialize(this);

	UInt32 runtimeUnitId(0);
	UInt32 heartbeatPeriod(0);

	if ( 3 == GetArgumentCount() )
	{
		runtimeUnitId = ::atoi(GetArgument(1).c_str());
		heartbeatPeriod = ::atoi(GetArgument(2).c_str());
		m_healthReporter.Initialize(runtimeUnitId, heartbeatPeriod);
	}
}

void CRuntimeUnit::InitDone(const bool& initStatus)
{
	std::string versionInfo(__DATE__);
	m_healthReporter.ReportInitDone(m_unitQueueName, versionInfo, initStatus);
}


Int32 CRuntimeUnit::Run()
{
	m_messenger.StartMsgProcessor();
	return m_unitReturnValue;
}

void CRuntimeUnit::NotifyShutdownPending()
{
	printf("Pending shutdown\n");
}

void CRuntimeUnit::ShutdownProcess()
{
	printf("Stopping the msg processor");
	m_messenger.StopMsgProcessor();
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

void CRuntimeUnit::SetIddle()
{
	m_healthReporter.SetIddle();
}

void CRuntimeUnit::SetBusy()
{
	m_healthReporter.SetBusy();
}

void CRuntimeUnit::SetError()
{
	m_healthReporter.SetError();
}

}
