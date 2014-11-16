#include "CProcessManager.h"
#include <Configuration/CConfigNode.h>
#include <Logger/Logger.h>
#include <algorithm>
#include "CProcessInfo.h"
#include "ISessionManager.h"
#include "IProcessControl.h"
#include "CProcessHandler.h"
#include <stdio.h>

namespace Controller
{

CProcessManager::CProcessManager( Runtime::ITimerManager& rTimerManager, 
																	ISessionManager& rSessionManager,
																	IProcessControl* pProcessControl )
:	m_sessionManager(rSessionManager)
, m_rTimerManager(rTimerManager)
, m_processControl(pProcessControl)
, m_processMonitorTimerId(-1)
, m_processMonitorInterval(5)
, m_sessionItemId(-1)
{
}

CProcessManager::~CProcessManager()
{
	for (tProcessIterator pIter = m_processList.begin() ; m_processList.end() != pIter ; ++pIter)
	{
		delete pIter->second;
	}
}

bool CProcessManager::Initialize( const Configuration::CConfigNode* configNode, 
																	const UInt32& defaultDebugLevelSettings )
{	
	bool retVal(false);
	if (0 == m_processControl)
	{
		return retVal;
	}
	
	// register the session notifications
	m_sessionItemId = m_sessionManager.RegisterSessionListener(this);
	
	// create and set up the timer for process monitoring
	m_processMonitorTimerId = m_rTimerManager.CreateTimer(this);
	m_rTimerManager.SetTimer( m_processMonitorTimerId , m_processMonitorInterval, m_processMonitorInterval);

	UInt32 unitId(1);
	const Configuration::CConfigNode* pProcessNode = configNode->GetFirstSubnode();

	while( 0 != pProcessNode )
	{
		CProcessInfo* pProcessInfo = new CProcessInfo(unitId, defaultDebugLevelSettings ,pProcessNode);
		
		if (0 != pProcessInfo)
		{
			if (m_processControl->AddProcessController( unitId, 
																									pProcessInfo->GetExecutableFileName(),
																									pProcessInfo->GetHeartbeatTimeout(),
																									pProcessInfo->GetDebugZoneSettings()))
			{			
				m_processList.insert(tProcessInfoMap::value_type( unitId , pProcessInfo ));
				// at least one process is configured
				
				++unitId;
				retVal = true;
			}
			else
			{
				delete pProcessInfo;
			}
		}

		pProcessNode = configNode->GetNextSubnode();
	}


	return retVal;
}

void CProcessManager::Shutdown()
{
}

bool CProcessManager::NotifySessionState(const tSessionState sessionState)
{
	switch( sessionState )
	{
	case eSessionState_Init1:
	case eSessionState_Init2:
	case eSessionState_Init3:
	{
		for(	tProcessIterator processIterator = m_processList.begin(); 
					processIterator != m_processList.end() ; 
					++processIterator)
		{
			if ( sessionState == processIterator->second->GetStartupGroup() )
			{
				/** start the process */
				m_processControl->StartProcess(processIterator->second->GetProcessID());
				
				/** update the internal CProcessInfo structure, with the busy state*/
				processIterator->second->SetUnitState(eStatus_Busy);
			}
		}
	};break;
	case eSessionState_Running:
	{
		m_rTimerManager.StartTimer( m_processMonitorTimerId );
	};break;
	case eSessionState_PendingShutdown:
	{
	};break;
	case eSessionState_Shutdown:
	{
	};break;
	default:;
	}
	
	return CheckProcessManagerState();
}

void CProcessManager::NotifyTimer( const Int32& timerId )
{
	if ( timerId == m_processMonitorTimerId )
	{
		UInt32 currentTickCount(m_rTimerManager.GetCurrentTime());
		for (tProcessIterator pIter = m_processList.begin() ; m_processList.end() != pIter ; ++pIter)
		{
			if ( pIter->second->HeartbeatTimeoutExpired(currentTickCount))
			{
				m_processControl->TerminateProcess( pIter->second->GetProcessID());
			}
		}
	}
}

void CProcessManager::NotifyUnitInitialized(	const UInt32& unitId, 
																							const std::string& processQueue, 
																							const std::string& unitVersion)
{
	UInt32 currentTickCount(m_rTimerManager.GetCurrentTime());
	tProcessIterator pIter = m_processList.find(unitId);
	
	if ( m_processList.end() != pIter )
	{
		pIter->second->SetUnitState( eStatus_Iddle );
		pIter->second->SetVersionInfo(unitVersion);
		pIter->second->SetQueueName(processQueue);
		pIter->second->UpdateHeartbeat(currentTickCount);
		m_sessionManager.ReportItemState(m_sessionItemId,CheckProcessManagerState());
	}
}

void CProcessManager::NotifyUnitHeartbeat(	const UInt32 unitId, const tProcessStatus& status )
{
	UInt32 currentTickCount(m_rTimerManager.GetCurrentTime());
	tProcessIterator pIter = m_processList.find(unitId);
	
	if ( m_processList.end() != pIter )
	{
		pIter->second->SetUnitState( status );
		pIter->second->UpdateHeartbeat(currentTickCount);
		m_sessionManager.ReportItemState(m_sessionItemId,CheckProcessManagerState());
	}	
}

void CProcessManager::GetRuntimeUnitShortnameList( tStringVector& runtimeShortnameList)
{
	runtimeShortnameList.resize( m_processList.size() + 1 );

	for (tProcessIterator pIter = m_processList.begin() ; m_processList.end() != pIter ; ++pIter)
	{
		runtimeShortnameList[pIter->first] = pIter->second->GetShortName() ;
	}
}

bool CProcessManager::CheckProcessManagerState()
{
	for (tProcessIterator pIter = m_processList.begin() ; m_processList.end() != pIter ; ++pIter)
	{
		if ( eStatus_Busy == pIter->second->GetUnitState())
		{
			return true;
		}
	}
	return false;
}

}
