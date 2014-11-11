#include "CSessionManager.h"
#include <algorithm>

namespace Controller
{
CSessionManager::CSessionManager(Runtime::ITimerManager& rTimerManager)
: m_rTimerManager(rTimerManager)
, m_currentItemId(0)
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
	if ( 0!= pListener)
	{
		++m_currentItemId;
	
		SessionItem item;
		item.pSessionStateListener = pListener;
		item.SessionItemState = true;
	
	
		m_items.insert(tSessionItemMap::value_type(m_currentItemId,item));
		return m_currentItemId;
	}
	return -1;	
}

void CSessionManager::ReportItemState(const Int32& itemId,const bool busy )
{
}

void CSessionManager::NotifyTimer( const Int32& timerId )
{
}

void CSessionManager::NotifySessionStateListeners(const tSessionState sessionState )
{
	NotifyAndUpdateItemState sessionStateNotifier(sessionState);
	
	std::for_each(m_items.begin() , m_items.end(), sessionStateNotifier );
}

bool CSessionManager::IsBusy()
{
	for (tSessionItemIterator iter = m_items.begin() ; m_items.end() != iter ; ++iter)
	{
		if (iter->second.SessionItemState)
		{
			return true;
		}
	}
	return false;
}


}
