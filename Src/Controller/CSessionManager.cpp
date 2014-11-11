#include "CSessionManager.h"

namespace Controller
{
CSessionManager::CSessionManager(Runtime::ITimerManager& rTimerManager)
: m_rTimerManager(rTimerManager)
, m_currentItemId(1)
,	m_init1TimerId(-1)
, m_init2TimerId(-1)
, m_init3TimerId(-1)
, m_pendingShutdownTimerId(-1)
{
}

CSessionManager::~CSessionManager()
{
}

bool CSessionManager::Initialize()
{
	m_init1TimerId = m_rTimerManager.CreateTimer(this);
	m_init2TimerId = m_rTimerManager.CreateTimer(this);
	m_init3TimerId = m_rTimerManager.CreateTimer(this);
	m_pendingShutdownTimerId = m_rTimerManager.CreateTimer(this);
	
	return true;
}

void CSessionManager::Shutdown()
{
}

Int32 CSessionManager::RegisterSessionListener( ISessionStateListener* pListener )
{
	return 0;
}

void CSessionManager::ReportItemState(const Int32& itemId,const bool busy )
{
}

void CSessionManager::NotifyTimer( const Int32& timerId )
{
}


}
