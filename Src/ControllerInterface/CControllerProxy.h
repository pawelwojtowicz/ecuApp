#ifndef CONTROLLER_CCONTROLLERPROXY_H
#define CONTROLLER_CCONTROLLERPROXY_H
#include <Runtime/CProxyBase.h>
#include "ControllerInterfaceConst.h"

namespace Controller
{
class CControllerProxy : public Runtime::CProxyBase
{
public:
	CControllerProxy(Runtime::IMessenger& rMessenger);
	virtual ~CControllerProxy();

	bool ReportInitDone(const UInt32& processId, const std::string& processQueue, const std::string& unitVersion);

	bool SendProcessHeartbeat(const UInt32 processId, const tProcessStatus& status );

	bool RequestShutdown();
	bool RequestRestart();

private:
	CControllerProxy(const CControllerProxy&);
	CControllerProxy& operator=(const CControllerProxy&);
};

}

#endif
