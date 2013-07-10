#include "CProcessManager.h"
#include <Configuration/CConfigNode.h>
#include <stdio.h>
#include "CProcessHandler.h"
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

	const Configuration::CConfigNode* pProcessNode = configNode->GetFirstSubnode();
	
	UInt32 unitId(1);

	while( 0 != pProcessNode )
	{
		CProcessHandler* pHandler = new CProcessHandler(unitId, pProcessNode);
		if (0 != pHandler  )
		{
			if ( pHandler->IsValid() )
			{
				m_processList.insert(tProcessMap::value_type( unitId, pHandler ) );
				++unitId;
			}
			else
			{
				delete pHandler;
			}
		}
		pProcessNode = configNode->GetNextSubnode();
	}

	for (tProcessIterator pIter = m_processList.begin() ; m_processList.end() != pIter ; ++pIter)
	{
		pIter->second->Start();
	}

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

void CProcessManager::NotifyUnitInitialized(	const UInt32& unitId, const std::string& processQueue, 
															const std::string& unitVersion)
{
	tProcessIterator pIter = m_processList.find( unitId );
	
	if ( m_processList.end() != pIter )
	{
		pIter->second->NotifyInitDone(processQueue, unitVersion);
	}
}

void CProcessManager::NotifyUnitHeartbeat(	const UInt32 unitId, const tProcessStatus& status )
{
	tProcessIterator pIter = m_processList.find( unitId );
	
	if ( m_processList.end() != pIter )
	{
		pIter->second->NotifyHeartbeat(status);
	}
}


}
