#include "CProcessManager.h"
#include <Configuration/CConfigNode.h>

namespace Controller
{
CProcessManager::CProcessManager( Runtime::ITimerManager& rTimerManager )
:	m_rTimerManager(rTimerManager)
, m_processMonitorTimerId(-1)
, m_processMonitorInterval(5)
{
}

CProcessManager::~CProcessManager()
{
}

bool CProcessManager::Initialize( const Configuration::CConfigNode* configNode )
{
	bool retVal(false);
	m_processMonitorTimerId = m_rTimerManager.CreateTimer(this);
	m_rTimerManager.SetTimer( m_processMonitorTimerId , m_processMonitorInterval, m_processMonitorInterval);

	return retVal;
}

void CProcessManager::Shutdown()
{
}

void CProcessManager::NotifyTimer( const Int32& timerId )
{
	if ( timerId == m_processMonitorTimerId )
	{

	}
}

}
