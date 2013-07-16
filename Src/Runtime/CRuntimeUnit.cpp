#include "CRuntimeUnit.h"
#include <cstdlib>

namespace Runtime
{
CRuntimeUnit::CRuntimeUnit( const std::string& runtimeUnitName , const std::string& unitQueueName )
: CExecutable(runtimeUnitName)
, m_loggingAgent()
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
	UInt32 runtimeUnitId(0);
	UInt32 heartbeatPeriod(0);
	UInt32 debugZoneLevel(0xFFFF);

	if ( 4 == GetArgumentCount() )
	{
		runtimeUnitId = ::atoi(GetArgument(1).c_str());
		heartbeatPeriod = ::atoi(GetArgument(2).c_str());
		debugZoneLevel = ::atoi(GetArgument(3).c_str());
		m_healthReporter.Initialize(runtimeUnitId, heartbeatPeriod);
	}
	m_loggingAgent.Initialize(runtimeUnitId);
	m_loggingAgent.SetDebugLevel(debugZoneLevel);

	m_messenger.Initialize(m_unitQueueName);
	m_controllerProxy.Initialize(this);
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
	RETAILMSG(WARNING, ("CRuntimeUnit::NotifyShutdownPending() - not implemented"));
}

void CRuntimeUnit::ShutdownProcess()
{
	RETAILMSG(WARNING, ("CRuntimeUnit::ShutdownProcess() - finishing the process"));
	m_messenger.StopMsgProcessor();
}


void CRuntimeUnit::Shutdown()
{
	m_messenger.Shutdown();

	m_loggingAgent.Shutdown();
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
