#include "CHealthReporter.h"
#include "ITimerManager.h"
#include <ControllerInterface/CControllerProxy.h>
#include <stdio.h>

namespace Runtime
{

CHealthReporter::CHealthReporter(	ITimerManager& rTimerManager, 
																	Controller::CControllerProxy& rControllerProxy)
: m_rTimerManager(rTimerManager)
, m_rControllerProxy(rControllerProxy)
, m_heartbeatTimerId(0)
, m_runtimeUnitId(0)
, m_unitState(Controller::eStatus_None)
{
}

CHealthReporter::~CHealthReporter()
{
}

void CHealthReporter::Initialize( UInt32 runtimeUnitId, UInt32 heartbeatPeriod )
{
	m_runtimeUnitId = runtimeUnitId;

	m_heartbeatTimerId = m_rTimerManager.CreateTimer(this);

	m_rTimerManager.SetTimer(m_heartbeatTimerId, heartbeatPeriod, heartbeatPeriod);
	m_rTimerManager.StartTimer(m_heartbeatTimerId);
}



void CHealthReporter::Shutdown()
{
	m_rTimerManager.StopTimer(m_heartbeatTimerId);
}


void CHealthReporter::NotifyTimer( const Int32& timerId )
{
	if (timerId == m_heartbeatTimerId)
	{
		m_rControllerProxy.SendProcessHeartbeat( m_runtimeUnitId, m_unitState );
	}
}

void CHealthReporter::ReportInitDone(const std::string& queueName, const std::string& versionInfo, const bool& status )
{
	m_rControllerProxy.ReportInitDone(m_runtimeUnitId, queueName, versionInfo);
}

void CHealthReporter::SetIddle()
{
	m_unitState = Controller::eStatus_Iddle;
}

void CHealthReporter::SetBusy()
{
	m_unitState = Controller::eStatus_Busy;
}
void CHealthReporter::SetError()
{
	m_unitState = Controller::eStatus_Error;
}

}
