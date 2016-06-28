#ifndef CONTROLLER_ICONTROLLERPROXY_H
#define CONTROLLER_ICONTROLLERPROXY_H
#include "ControllerTypes.h"
#include <Global/GlobalTypes.h>

namespace Controller
{
class IControllerListener;
class CPublicProcessInfo;

class IControllerProxy
{
public:
	IControllerProxy() {};
	virtual ~IControllerProxy() {};

	virtual bool ReportInitDone(	const UInt32& processId, 
																const std::string& processQueue, 
																const std::string& unitVersion) = 0;

	virtual bool SendProcessHeartbeat(const UInt32 processId, const tProcessStatus& status ) = 0;
	
	virtual bool GetCurrentProcessInfo( CPublicProcessInfo& processInfo) = 0;

	virtual bool RequestShutdown() = 0;
	virtual bool RequestRestart() = 0;
	virtual bool RestartDevice() = 0;
	virtual bool DeactivateWatchdog() = 0;

private:
	IControllerProxy(const IControllerProxy&);
	IControllerProxy& operator=(const IControllerProxy&);
};

}

#endif
