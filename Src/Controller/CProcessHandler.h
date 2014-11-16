#ifndef CONTROLLER_CPROCESSHANDLER_H
#define CONTROLLER_CPROCESSHANDLER_H
#include <GlobalTypes.h>
#include <UCL/CThread.h>
#include <ControllerInterface/ControllerTypes.h>



namespace Controller
{
class IProcessStatusReporter;

class CProcessHandler: public UCL::CThread
{
public:
	CProcessHandler(	const UInt32& processID, 
										const std::string& executableName,
										const UInt32& heartbeatPeriod,
										const UInt32& debugZoneSetting,
										IProcessStatusReporter& rProcessStatusReporter
  );
	virtual ~CProcessHandler();
	
	void TerminateProcess();
	
private:

	virtual void Run();
	
private:
	/** process ID, needed for status reporting*/
	UInt32 m_processID;
	
	/** executable filename */
	std::string m_executableFileName;

	/** processID rendered into the string */
	std::string m_processIDString;
	
	/** heartbeat period string*/
	std::string m_heartbeatPeriodString;
	
	/** debug zone settings string */
	std::string m_debugZoneSettingString;
	
	pid_t m_processId;
	
	IProcessStatusReporter& m_rProcessStatusReporter;
};
}

#endif
