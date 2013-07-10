#include "CProcessHandler.h"
#include <Configuration/CConfigNode.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

static char sCfg_ExecutableName[] = {"CommandLine"};
static char sCfg_StartupGroup[] = {"StartupGroup"};
static char sCfg_ShutdownGroup[] = {"ShutdownGroup"};

namespace Controller
{
CProcessHandler::CProcessHandler( const UInt32& unitId, const Configuration::CConfigNode* pConfigNode )
: UCL::CThread( pConfigNode->GetConfigNodeName() )
, m_processID(unitId)
, m_hearbeatTimeout(2)
, m_running(true)
{
	m_executableFileName = pConfigNode->GetParameter(sCfg_ExecutableName)->GetString(std::string());
	m_startupGroup = pConfigNode->GetParameter(sCfg_StartupGroup)->GetUInt8(0);
	m_shutdownGroup = pConfigNode->GetParameter(sCfg_ShutdownGroup)->GetUInt8(0);
}

CProcessHandler::~CProcessHandler()
{
}

bool CProcessHandler::IsValid()
{
	return true;
}

void CProcessHandler::NotifyHeartbeat(const tProcessStatus& status)
{
	printf("processId=[%s] status=%d\n", GetThreadName().c_str(), status);
	m_processStatus = status;
}

void CProcessHandler::NotifyInitDone(const std::string& queueName, const std::string& versionInformation)
{
	m_queueName = queueName;
	m_versionInformation = versionInformation;

	printf("process %s reported initDone. Queue=%s, versionString=%s\n", GetThreadName().c_str(), m_queueName.c_str(), m_versionInformation.c_str() );
}


void CProcessHandler::Run()
{
	pid_t processId;
	Int32 returnValue(0);

	char runtimeIdStringBuffer[10];
	char heartbeatPeriodStringBuffer[10];
	sprintf(runtimeIdStringBuffer, "%d", m_processID );
	sprintf(heartbeatPeriodStringBuffer, "%d", m_hearbeatTimeout );

	while ( m_running )
	{
		processId = fork();

		printf("forking %d\n", processId);
		
		if ( 0 == processId )
		{
			printf("starting[%s]\n",m_executableFileName.c_str());
			execlp(m_executableFileName.c_str(),m_executableFileName.c_str(), runtimeIdStringBuffer, heartbeatPeriodStringBuffer,0);
			printf("errno[%s]\n",strerror(errno));

			sleep(10);
		}
		else
		{
			printf("wait for ending the process\n");
			waitpid(processId, &returnValue, 0 );
			printf("processFinished\n");

		}
	}

}

}