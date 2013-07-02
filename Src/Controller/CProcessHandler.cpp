#include "CProcessHandler.h"
#include <Configuration/CConfigNode.h>
#include <unistd.h>
#include <stdio.h>

static char sCfg_ExecutableName[] = {"CommandLine"};
static char sCfg_StartupGroup[] = {"StartupGroup"};
static char sCfg_ShutdownGroup[] = {"ShutdownGroup"};

namespace Controller
{
CProcessHandler::CProcessHandler( const UInt32& unitId, const Configuration::CConfigNode* pConfigNode )
: UCL::CThread( pConfigNode->GetConfigNodeName() )
, m_processID(unitId)
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
	m_processStatus = status;
}

void CProcessHandler::NotifyInitDone(const std::string& queueName, const std::string& versionInformation)
{
	m_queueName = queueName;
	m_versionInformation = versionInformation;

}


void CProcessHandler::Run()
{
//int execvp(const char *file, char *const argv[]);
//int execvpe(const char *file, char *const argv[],char *const envp[]);

}

}
