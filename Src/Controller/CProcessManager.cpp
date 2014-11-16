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
																									defaultDebugLevelSettings))
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
	return true;
}

void CProcessManager::NotifyTimer( const Int32& timerId )
{
	if ( timerId == m_processMonitorTimerId )
	{

	}
}

void CProcessManager::NotifyUnitInitialized(	const UInt32& unitId, const std::string& processQueue, 
															const std::string& unitVersion)
{
}

void CProcessManager::NotifyUnitHeartbeat(	const UInt32 unitId, const tProcessStatus& status )
{
}

void CProcessManager::GetRuntimeUnitShortnameList( tStringVector& runtimeShortnameList)
{
	runtimeShortnameList.resize( m_processList.size() + 1 );

	for (tProcessIterator pIter = m_processList.begin() ; m_processList.end() != pIter ; ++pIter)
	{
		runtimeShortnameList[pIter->first] = pIter->second->GetShortName() ;
	}

}


}
