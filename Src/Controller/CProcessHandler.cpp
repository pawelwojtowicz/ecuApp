#include "CProcessHandler.h"
#include <Logger/CLogManager.h>
#include <Logger/Logger.h>
#include <ControllerInterface/IProcessStatusReporter.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

namespace Controller
{
CProcessHandler::CProcessHandler( const UInt32& processID, 
																	const std::string& executableName,
																	const UInt32& heartbeatPeriod,
																	const UInt32& debugZoneSetting,
																	IProcessStatusReporter& rProcessStatusReporter
 )
: UCL::CThread( executableName )
, m_processID(processID)
, m_executableFileName(executableName)
, m_heartbeatPeriodString()
, m_debugZoneSettingString()
, m_processId(0)
, m_rProcessStatusReporter(rProcessStatusReporter)
{
	char helperBuffer[20];
	
	sprintf(helperBuffer, "%d", m_processID );
	m_processIDString = helperBuffer;

	sprintf(helperBuffer, "%d", heartbeatPeriod );
	m_heartbeatPeriodString = helperBuffer;

	sprintf(helperBuffer, "%d", debugZoneSetting );
	m_debugZoneSettingString = helperBuffer;
}

CProcessHandler::~CProcessHandler()
{
}

void CProcessHandler::Run()
{
	Int32 returnValue(0);

	m_processId = fork();
		
	if ( 0 == m_processId )
	{
		RETAILMSG(INFO, ( "Starting process %s", GetThreadName().c_str() ) );
		execlp(	m_executableFileName.c_str(),
						m_executableFileName.c_str(), 
						m_processIDString.c_str(), 
						m_heartbeatPeriodString.c_str(),
						m_debugZoneSettingString.c_str(),
						NULL);
		RETAILMSG(ERROR, ("Failed to start [%s], error=[%s]", GetThreadName().c_str(), strerror(errno)));
		exit(-1);
	}
	else
	{
		RETAILMSG(INFO,("Process [%s] is started", GetThreadName().c_str()));
		waitpid(m_processId, &returnValue, 0 );
		m_processId = 0;
		RETAILMSG(INFO,("Process [%s] is finished - return Value [%d]",GetThreadName().c_str(), returnValue));
		sleep(10);
		m_rProcessStatusReporter.SendProcessStatus(m_processID, eStatus_Iddle);
	}
}

void CProcessHandler::TerminateProcess()
{
	if ( 0 != m_processId )
	{
		kill( m_processId , SIGTERM );
		sleep(2);
		kill( m_processId , SIGKILL );
		m_processId = 0;
	}
}

}
