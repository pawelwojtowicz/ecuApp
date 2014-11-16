#ifndef CONTROLLER_IPROCESSCONTROL_H
#define CONTROLLER_IPROCESSCONTROL_H

namespace Controller
{
class IProcessControl
{
public:
	IProcessControl() {};
	virtual ~IProcessControl() {};
	
public:
	virtual bool AddProcessController(	UInt32 processID, 
																			std::string executableName,
																			UInt32 heartbeatPeriod,
																			UInt32 debugZoneSetting) = 0;
	
	virtual void StartProcess( Int32 processHandlerID ) = 0;
	
	virtual void TerminateProcess( Int32 processHandlerID ) = 0;

private:
	IProcessControl(const IProcessControl&);
	IProcessControl& operator=(const IProcessControl&);
};
}
#endif //CONTROLLER_IPROCESSCONTROL_H
