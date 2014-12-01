#ifndef CONTROLLER_CCONTROLLERSTUB_H
#define CONTROLLER_CCONTROLLERSTUB_H

#include <Runtime/CStubBase.h> 
#include "IProcessStatusReporter.h"
#include <Runtime/CSharedStorage.h>

namespace Runtime
{
class CMessenger;
class CMessage;
}

namespace Controller
{
class IControllerServices;
class CPublicProcessInfo;

class CControllerStub: public Runtime::CStubBase
										 , public IProcessStatusReporter
{
public:
	CControllerStub( Runtime::IMessenger& rMessenger );
	virtual ~CControllerStub();

	virtual bool Initialize(IControllerServices* pControllerServices);
	virtual bool Shutdown();
	
	virtual bool PublishProcessInfo( CPublicProcessInfo& processInfo);

	virtual bool BroadcastPendingShutdown();

	virtual bool BroadcastShutdown();

private: 	
	//Implementation of IProcessStatusReporter
	virtual bool SendProcessStatus(const UInt32 processId, const tProcessStatus& status );

private:
	virtual void HandleMessage(Runtime::CMessage& rMessage);

private:
	IControllerServices* m_pControllerServices;
	
	Runtime::CSharedStorage m_sharedStorage;
};

}
#endif //CONTROLLER_CONTROLLERSTUB_H
