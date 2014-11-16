#include "CProcessControl.h"
#include "CProcessHandler.h"
#include "ControllerInterface/IProcessStatusReporter.h"

namespace Controller
{

CProcessControl::CProcessControl(IProcessStatusReporter& rProcessStatusReporter)
: m_rProcessStatusReporter(rProcessStatusReporter)
{
}

CProcessControl::~CProcessControl()
{
}


bool CProcessControl::AddProcessController(	UInt32 processID, 
																			std::string executableName,
																			UInt32 heartbeatPeriod,
																			UInt32 debugZoneSetting)
{
	CProcessHandler* pProcessHandler = new CProcessHandler(processID, 
																												executableName,
																												heartbeatPeriod,
																												debugZoneSetting,
																												m_rProcessStatusReporter);
																												
	if ( 0 != pProcessHandler )
	{
		m_processHandlers.insert(tProcessHandlerMap::value_type(processID, pProcessHandler));
		return true;
	}
	return false;
}
	
void CProcessControl::StartProcess( Int32 processHandlerID )
{
	tProcessHandlerIterator phIter = m_processHandlers.find(processHandlerID);
	
	if (m_processHandlers.end() != phIter )
	{
		phIter->second->Start();
	}
}
	
void CProcessControl::TerminateProcess( Int32 processHandlerID )
{
	tProcessHandlerIterator phIter = m_processHandlers.find(processHandlerID);
	
	if (m_processHandlers.end() != phIter )
	{
		phIter->second->TerminateProcess();
	}
}

}
