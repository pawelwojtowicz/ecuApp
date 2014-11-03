#include "CProcessInfo.h"
#include <Configuration/CConfigNode.h>
#include <UCL/SystemEnvironment.h>
#include <Logger/CLogManager.h>


namespace Controller
{

static char sCfg_ExecutableName[] 	= {"CommandLine"};
static char sCfg_StartupGroup[] 		= {"StartupGroup"};
static char sCfg_ShutdownGroup[] 		= {"ShutdownGroup"};
static char sCfg_HeartbeatPeriod[]	= {"HeartbeatPeriod"};
static char sCfg_ProcessDebugLevel[]= {"DebugLevel"};
static char cCfg_ProcessShortname[]	= {"Shortname"};

CProcessInfo::CProcessInfo(	const UInt32& unitId, 
							const UInt32& defaultDebugZones,
							const Configuration::CConfigNode* pConfigNode)
: m_processID(unitId)
, m_executableFileName()
, m_debugZoneSettings(defaultDebugZones)
, m_shortName()
, m_startupGroup(0)
, m_shutdownGroup(0)
, m_hearbeatTimeout(5)
, m_lastHeartbeat(0)
, m_queueName()
, m_versionInformation()
{
	std::string executableFileName = pConfigNode->GetParameter(sCfg_ExecutableName)->GetString(std::string());
	m_executableFileName = UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_App, executableFileName);
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
								
CProcessInfo::~CProcessInfo()
{
}

const UInt32 CProcessInfo::GetProcessID() const
{
	return m_processID;
}

const std::string& CProcessInfo::GetExecutableFileName() const
{
	return m_executableFileName;
}

const UInt32 CProcessInfo::GetDebugZoneSettings() const
{
	return m_debugZoneSettings;
}

const std::string& CProcessInfo::GetShortName() const
{
	return m_shortName;
}

const UInt8 CProcessInfo::GetStartupGroup() const
{
	return m_startupGroup;
}

const UInt8 CProcessInfo::GetShutdownGroup() const
{
	return m_shutdownGroup;
}

const UInt32 CProcessInfo::GetHeartbeatTimeout() const
{
	return m_hearbeatTimeout;
}

}
