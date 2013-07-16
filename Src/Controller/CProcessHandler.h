#ifndef CONTROLLER_CPROCESSHANDLER_H
#define CONTROLLER_CPROCESSHANDLER_H
#include <GlobalTypes.h>
#include <UCL/CThread.h>
#include <ControllerInterface/ControllerTypes.h>

namespace Configuration
{
class CConfigNode;
}

namespace Controller
{

class CProcessHandler: public UCL::CThread
{
public:
	CProcessHandler(	const UInt32& unitId, 
										const UInt32& defaultDebugZones,
										const Configuration::CConfigNode* pConfigNode );
	virtual ~CProcessHandler();

	bool IsValid();

	void NotifyHeartbeat(const tProcessStatus& status);

	void NotifyInitDone(const std::string& queueName, const std::string& versionInformation);

	const std::string& GetShortname() { return m_shortName; };

	virtual void Run();

private:
	UInt32 m_processID;
	std::string m_executableFileName;
	UInt8 m_startupGroup;
	UInt8 m_shutdownGroup;
	UInt32 m_debugZoneSettings;


	bool m_running;
	
	tProcessStatus m_processStatus;

	std::string m_queueName;

	std::string m_versionInformation;

	std::string m_shortName;

	UInt32 m_lastHeartbeat;

	UInt32 m_hearbeatTimeout;
};
}

#endif
