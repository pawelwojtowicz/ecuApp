#include "CControllerProxy.h"
#include <Runtime/IMessenger.h>
#include "ControllerInterfaceConst.h"

namespace Controller
{
CControllerProxy::CControllerProxy(Runtime::IMessenger& rMessenger)
: Runtime::CProxyBase(rMessenger, s_ControllerQueueName)
{
}

CControllerProxy::~CControllerProxy()
{
}

bool CControllerProxy::ReportInitDone(const UInt32& processId, const std::string& processQueue, const std::string& unitVersion)
{
	return true;
}

bool CControllerProxy::SendProcessHeartbeat(const UInt32 processId, const tProcessStatus& status )
{
	return true;
}

bool CControllerProxy::RequestShutdown()
{
	return true;
}

bool CControllerProxy::RequestRestart()
{
	return true;
}
}
