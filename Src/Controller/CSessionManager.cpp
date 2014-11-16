#include "CSessionManager.h"
#include <Configuration/CConfigNode.h>
#include <algorithm>

namespace Controller
{
static char sCfg_InitStep1Timeout[] 			= {"Init1Timeout"};
static char sCfg_InitStep2Timeout[] 			= {"Init2Timeout"};
static char sCfg_InitStep3Timeout[] 			= {"Init3Timeout"};
static char sCfg_PendingShutdownTimeout[]	= {"PendingShutdownTimeout"};
static char sCfg_ShutdownTimeout[]				= {"ShutdownTimeout"};

CSessionManager::CSessionManager(Runtime::ITimerManager& rTimerManager)
: m_rTimerManager(rTimerManager)
, m_currentItemId(0)
, m_timeoutTimerId(-1)
,	m_init1Timeout(1)
, m_init2Timeout(2)
, m_init3Timeout(3)
, m_pendingShutdownTimeout(4)
,	m_shutdownTimeout(5)
, m_currentSessionState(eSessionState_Iddle)
{
}

CSessionManager::~CSessionManager()
{
}

bool CSessionManager::Initialize(const Configuration::CConfigNode* pConfigNode)
{
	if ( 0 != pConfigNode )
	{
		m_init1Timeout = pConfigNode->GetParameter(sCfg_InitStep1Timeout)->GetUInt32(m_init1Timeout);
		m_init2Timeout = pConfigNode->GetParameter(sCfg_InitStep2Timeout)->GetUInt32(m_init2Timeout);
		m_init3Timeout = pConfigNode->GetParameter(sCfg_InitStep3Timeout)->GetUInt32(m_init3Timeout);
		m_pendingShutdownTimeout = pConfigNode->GetParameter(sCfg_PendingShutdownTimeout)->GetUInt32(m_pendingShutdownTimeout);
		m_shutdownTimeout = pConfigNode->GetParameter(sCfg_ShutdownTimeout)->GetUInt32(m_shutdownTimeout);
	}
	
	m_timeoutTimerId = m_rTimerManager.CreateTimer(this);
	
	DispatchSessionEvent(eEvent_PhaseCompleted);
	
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
		item.SessionItemState = false;
	
	
		m_items.insert(tSessionItemMap::value_type(m_currentItemId,item));
		return m_currentItemId;
	}
	return -1;	
}

void CSessionManager::ReportItemState(const Int32& itemId,const bool busy )
{
	bool was( IsBusy() );
	tSessionItemIterator pIter(m_items.find(itemId));
	if ( m_items.end() != pIter )
	{
		pIter->second.SessionItemState = busy;
	}
	
	if (was && !IsBusy() )
	{
		DispatchSessionEvent(eEvent_PhaseCompleted);	
	}
}

void CSessionManager::NotifyTimer( const Int32& timerId )
{
	if (timerId == m_timeoutTimerId)
	{
		DispatchSessionEvent(eEvent_TimeoutElapsed);
	}
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

void CSessionManager::ShutdownRequest()
{
	DispatchSessionEvent(eEvent_ShutdownRequest);

}

tSessionState CSessionManager::EvaluateNextState( const tSessionEvents event )
{
	tSessionState newState(m_currentSessionState);
	
	switch (m_currentSessionState)
	{
	case eSessionState_Iddle:
	{
		if ( eEvent_ShutdownRequest == event )
		{
			if ( IsBusy() )
			{
				newState = eSessionState_PendingShutdown;
			}
			else
			{
				newState = eSessionState_Shutdown;
			}

		}
		else
		{
			newState = eSessionState_Init1;
		}
	};break;
	case eSessionState_Init1:
	{
		if ( eEvent_ShutdownRequest == event )
		{
			if ( IsBusy() )
			{
				newState = eSessionState_PendingShutdown;
			}
			else
			{
				newState = eSessionState_Shutdown;
			}

		}
		else
		{
			newState = eSessionState_Init2;
		}
	};break;	
	case eSessionState_Init2:
	{
		if ( eEvent_ShutdownRequest == event )
		{
			if ( IsBusy() )
			{
				newState = eSessionState_PendingShutdown;
			}
			else
			{
				newState = eSessionState_Shutdown;
			}

		}
		else
		{
			newState = eSessionState_Init3;
		}
	};break;
	case eSessionState_Init3:
	{
		if ( eEvent_ShutdownRequest == event )
		{
			if ( IsBusy() )
			{
				newState = eSessionState_PendingShutdown;
			}
			else
			{
				newState = eSessionState_Shutdown;
			}

		}
		else
		{
			newState = eSessionState_Running;
		}
	};break;
	case eSessionState_Running:
	{
		if ( eEvent_ShutdownRequest == event )
		{
			if ( IsBusy() )
			{
				newState = eSessionState_PendingShutdown;
			}
			else
			{
				newState = eSessionState_Shutdown;
			}
		}
	};break;
	case eSessionState_PendingShutdown:
	{
		if ( eEvent_ShutdownRequest != event )
		{
			newState = eSessionState_Shutdown;
		}
	};break;
	case eSessionState_Shutdown:
		if ( eEvent_ShutdownRequest != event )
		{
			newState = eSessionState_PowerOff;
		}

	default:;
	}
	
	return newState;
	
}

UInt32 CSessionManager::GetPhaseTimeout(tSessionState sessionState)
{
	UInt32 timeoutValue(0);
	
	switch ( sessionState )
	{
		case eSessionState_Init1:
		{
			timeoutValue = m_init1Timeout;
		};break;
		case eSessionState_Init2:
		{
			timeoutValue = m_init2Timeout;
		};break;
		case eSessionState_Init3:
		{
			timeoutValue = m_init3Timeout;
		};break;
		case eSessionState_PendingShutdown:
		{
			timeoutValue = m_pendingShutdownTimeout;
		};break;
		case eSessionState_Shutdown:
		{
			timeoutValue = m_shutdownTimeout;
		};break;
		default:;
	};
	return timeoutValue;
}

void CSessionManager::DispatchSessionEvent(tSessionEvents event)
{
	do
	{
		tSessionState newSessionState(EvaluateNextState(event));
		if ( newSessionState != m_currentSessionState )
		{
			m_rTimerManager.StopTimer(m_timeoutTimerId);
			m_currentSessionState = newSessionState;
			
			NotifySessionStateListeners(m_currentSessionState);
		}
		
		if ( ( m_currentSessionState < eSessionState_Running || eSessionState_PendingShutdown == m_currentSessionState || eSessionState_Shutdown == m_currentSessionState) && !IsBusy() )
		{
			event = eEvent_PhaseCompleted;
		}
		else
		{
			break;
		}
	} 
	while ( ( eSessionState_Iddle != m_currentSessionState )  && ( eSessionState_Running != m_currentSessionState ));
	
	UInt32 newTimeout( GetPhaseTimeout(m_currentSessionState));

	if ( 0 != newTimeout )
	{
		m_rTimerManager.SetTimer(m_timeoutTimerId,newTimeout,0);
		m_rTimerManager.StartTimer(m_timeoutTimerId);
	}
}


}
