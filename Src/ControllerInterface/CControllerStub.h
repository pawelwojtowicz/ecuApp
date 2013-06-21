#ifndef CONTROLLER_CCONTROLLERSTUB_H
#define CONTROLLER_CCONTROLLERSTUB_H

#include <Runtime/CStubBase.h> 

namespace Runtime
{
class CMessenger;
class CMessage;
}

namespace Controller
{
class IControllerServices;

class CControllerStub: public Runtime::CStubBase
{
public:
	CControllerStub( Runtime::IMessenger& rMessenger );
	virtual ~CControllerStub();

	virtual bool Initialize(IControllerServices* pControllerServices);
	virtual bool Shutdown();

	virtual void HandleMessage(Runtime::CMessage& rMessage);



private:
	IControllerServices* m_pControllerServices;
};

}
#endif //CONTROLLER_CONTROLLERSTUB_H
