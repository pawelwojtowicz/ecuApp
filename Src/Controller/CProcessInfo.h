#ifndef CONTROLLER_CPROCESSINFO_H
#define CONTROLLER_CPROCESSINFO_H
#include <GlobalTypes.h>
#include <ControllerInterface/ControllerTypes.h>

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
	
	const tSessionState GetStartupGroup() const;
	
	const UInt8 GetShutdownGroup() const;
	
	const UInt32 GetHeartbeatTimeout() const;
	
	const std::string& GetProcessName() const;
	
	void SetUnitState(const tProcessStatus unitState) { m_unitState = unitState;};
	tProcessStatus GetUnitState() { return m_unitState; };
	
	void UpdateHeartbeat(const UInt32 currentTickCount );
	bool HeartbeatTimeoutExpired(const UInt32 currentTickCount);
	
	const std::string& GetVersionInfo() { return m_versionInformation; };
	
	const std::string& GetQueueName() { return m_queueName; };

	void SetVersionInfo(const std::string& versionInfo) { m_versionInformation= versionInfo; };
	
	void SetQueueName(const std::string& queueName) { m_queueName = queueName; };
	
private:
	std::string m_processName;
	
	UInt32 m_processID;
	
	std::string m_executableFileName;
	
	UInt32 m_debugZoneSettings;

	std::string m_shortName;

	tSessionState m_startupGroup;
	
	UInt8 m_shutdownGroup;

	UInt32 m_hearbeatTimeout;
	
	UInt32 m_nextDeadlineForHeartbeat;
	
	std::string m_queueName;
	
	std::string m_versionInformation;
	
	tProcessStatus m_unitState;
};
}

#endif //CONTROLLER_PROCESSINFO_H
