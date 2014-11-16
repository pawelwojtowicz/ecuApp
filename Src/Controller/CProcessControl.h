#ifndef CONTROLLER_CPROCESSCONTROL_H
#define CONTROLLER_CPROCESSCONTROL_H
#include "IProcessControl.h"
namespace Controller
{
class CProcessHandler;

class CProcessControl:public IProcessControl
{
	typedef std::map<UInt32, CProcessHandler*> tProcessHandlerMap;
	typedef tProcessHandlerMap::iterator tProcessHandlerIterator;
public:
	CProcessControl();
	virtual ~CProcessControl();


private:
	virtual bool AddProcessController(	UInt32 processID, 
																			std::string executableName,
																			UInt32 heartbeatPeriod,
																			UInt32 debugZoneSetting);
	
	virtual void StartProcess( Int32 processHandlerID );
	
	virtual void TerminateProcess( Int32 processHandlerID );

private:
	tProcessHandlerMap m_processHandlers;
};
}

#endif
