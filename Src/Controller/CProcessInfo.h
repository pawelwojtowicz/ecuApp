#ifndef CONTROLLER_CPROCESSINFO_H
#define CONTROLLER_CPROCESSINFO_H
#include <GlobalTypes.h>

namespace Configuration
{
class CConfigNode;
}

namespace Controller
{
class CProcessInfo
{
public:
	CProcessInfo(	const UInt32& unitId, 
								const UInt32& defaultDebugZones,
								const Configuration::CConfigNode* pConfigNode);
								
	virtual ~CProcessInfo();
	
	const UInt32 GetProcessID() const;
	
	const std::string& GetExecutableFileName() const;
	
	const UInt32 GetDebugZoneSettings() const;
	
	const std::string& GetShortName() const;
	
	const UInt8 GetStartupGroup() const;
	
	const UInt8 GetShutdownGroup() const;
	
	const UInt32 GetHeartbeatTimeout() const;
	
	const std::string& GetProcessName() const;

private:
	std::string m_processName;
	
	UInt32 m_processID;
	
	std::string m_executableFileName;
	
	UInt32 m_debugZoneSettings;

	std::string m_shortName;

	UInt8 m_startupGroup;
	
	UInt8 m_shutdownGroup;

	UInt32 m_hearbeatTimeout;
	
	UInt32 m_lastHeartbeat;
	
	std::string m_queueName;
	
	std::string m_versionInformation;

};
}

#endif //CONTROLLER_PROCESSINFO_H
