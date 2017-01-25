#ifndef CONTROLLER_CCONTROLLERPROXY_H
#define CONTROLLER_CCONTROLLERPROXY_H
#include <Runtime/CProxyBase.h>
#include <Runtime/CSharedStorage.h>
#include "ControllerTypes.h"

namespace Controller
{
class IControllerListener;
class CPublicProcessInfo;

class CControllerProxy : public Runtime::CProxyBase
{
public:
	CControllerProxy(Runtime::IMessenger& rMessenger);
	virtual ~CControllerProxy();

	bool Initialize(IControllerListener* pListener);

	bool ReportInitDone(	const UInt32& processId, 
												const std::string& processQueue, 
												const std::string& unitVersion);

	bool SendProcessHeartbeat(const UInt32 processId, const tProcessStatus& status );
	
	bool GetCurrentProcessInfo( CPublicProcessInfo& processInfo);

	bool RequestShutdown();
	bool RequestRestart();
	bool RestartDevice();
	bool DeactivateWatchdog();

private:
	void HandleMessage(Runtime::CMessage& rMessage);

	CControllerProxy(const CControllerProxy&);
	CControllerProxy& operator=(const CControllerProxy&);
	
	Runtime::CSharedStorage m_sharedStorage;

	IControllerListener* m_pControllerListener;
};

}

#endif
