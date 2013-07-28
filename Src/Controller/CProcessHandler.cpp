#include "CProcessHandler.h"
#include <Configuration/CConfigNode.h>
#include <Logger/CLogManager.h>
#include <Logger/Logger.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

static char sCfg_ExecutableName[] 	= {"CommandLine"};
static char sCfg_StartupGroup[] 		= {"StartupGroup"};
static char sCfg_ShutdownGroup[] 		= {"ShutdownGroup"};
static char sCfg_HeartbeatPeriod[]	= {"HeartbeatPeriod"};
static char sCfg_ProcessDebugLevel[]= {"DebugLevel"};
static char cCfg_ProcessShortname[]	= {"Shortname"};
namespace Controller
{
CProcessHandler::CProcessHandler( const UInt32& unitId, 
																	const UInt32& defaultDebugZones,
																	const Configuration::CConfigNode* pConfigNode )
: UCL::CThread( pConfigNode->GetConfigNodeName() )
, m_processID(unitId)
, m_executableFileName()
, m_startupGroup(0)
, m_shutdownGroup(0)
, m_debugZoneSettings(defaultDebugZones)
, m_running(true)
, m_processStatus(eStatus_None)
, m_queueName()
, m_versionInformation()
, m_shortName()
, m_lastHeartbeat(0)
, m_hearbeatTimeout(5)
{
	m_executableFileName = pConfigNode->GetParameter(sCfg_ExecutableName)->GetString(std::string());
	m_startupGroup = pConfigNode->GetParameter(sCfg_StartupGroup)->GetUInt8(0);
	m_shutdownGroup = pConfigNode->GetParameter(sCfg_ShutdownGroup)->GetUInt8(0);
	m_hearbeatTimeout = pConfigNode->GetParameter(sCfg_HeartbeatPeriod)->GetUInt32(m_hearbeatTimeout);
	m_shortName	= pConfigNode->GetParameter(cCfg_ProcessShortname)->GetString("tmp");
	const Configuration::CConfigNode* pDebugLevelConfig = pConfigNode->GetConfigNode(sCfg_ProcessDebugLevel);
	if ( 0 != pDebugLevelConfig )
	{
		m_debugZoneSettings = Logger::CLogManager::ReadDebugLevelConfig(pDebugLevelConfig);
	}
}

CProcessHandler::~CProcessHandler()
{
}

bool CProcessHandler::IsValid()
{
	// check if file exists, check the heartbeat period, 
	return true;
}

void CProcessHandler::NotifyHeartbeat(const tProcessStatus& status)
{
	m_processStatus = status;
	RETAILMSG(INFO, ("Heartbeat from process [%s] received - status = [%d]", GetThreadName().c_str(), m_processStatus));	
}

void CProcessHandler::NotifyInitDone(const std::string& queueName, const std::string& versionInformation)
{
	m_queueName = queueName;
	m_versionInformation = versionInformation;

	RETAILMSG(INFO, ("InitDone received from [%s]. Queue=%s, VersionInfo=%s", GetThreadName().c_str(), m_queueName.c_str(), m_versionInformation.c_str() ) );
}


void CProcessHandler::Run()
{
	pid_t processId;
	Int32 returnValue(0);

	char runtimeIdStringBuffer[10];
	char heartbeatPeriodStringBuffer[10];
	char debugZoneSettingBuffer[10];
	sprintf(runtimeIdStringBuffer, "%d", m_processID );
	sprintf(heartbeatPeriodStringBuffer, "%d", m_hearbeatTimeout );
	sprintf(debugZoneSettingBuffer, "%d", m_debugZoneSettings );

	while ( m_running )
	{
		processId = fork();
		
		if ( 0 == processId )
		{
			RETAILMSG(INFO, ( "Starting process %s", GetThreadName().c_str() ) );
			execlp(	m_executableFileName.c_str(),
							m_executableFileName.c_str(), 
							runtimeIdStringBuffer, 
							heartbeatPeriodStringBuffer,
							debugZoneSettingBuffer,
							NULL);
			RETAILMSG(ERROR, ("Failed to start [%s], error=[%s]", GetThreadName().c_str(), strerror(errno)));

			sleep(10);
		}
		else
		{
			RETAILMSG(INFO,("Process [%s] is started", GetThreadName().c_str()));
			waitpid(processId, &returnValue, 0 );
			RETAILMSG(INFO,("Process [%s] is finished - return Value [%d]",GetThreadName().c_str(), returnValue));
		}
	}
	
	m_processStatus = eStatus_Stopped;
	RETAILMSG(INFO,("ProcessHandler for [%s] is stopped",GetThreadName().c_str()));

}

void CProcessHandler::StopProcessHandler()
{
	m_running = false;
}

}
