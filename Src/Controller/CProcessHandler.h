#ifndef CONTROLLER_CPROCESSHANDLER_H
#define CONTROLLER_CPROCESSHANDLER_H
#include <GlobalTypes.h>
#include <UCL/CThread.h>
#include <ControllerInterface/ControllerInterfaceConst.h>

namespace Configuration
{
class CConfigNode;
}

namespace Controller
{

class CProcessHandler: public UCL::CThread
{
public:
	CProcessHandler( const UInt32& unitId, const Configuration::CConfigNode* pConfigNode );
	virtual ~CProcessHandler();

	bool IsValid();

	void NotifyHeartbeat(const tProcessStatus& status);

	void NotifyInitDone(const std::string& queueName, const std::string& versionInformation);

	virtual void Run();

private:
	UInt32 m_processID;
	std::string m_executableFileName;
	UInt8 m_startupGroup;
	UInt8 m_shutdownGroup;

	bool m_running;
	
	tProcessStatus m_processStatus;

	std::string m_queueName;

	std::string m_versionInformation;

	UInt32 m_lastHeartbeat;

	UInt32 m_hearbeatTimeout;
};
}

#endif
