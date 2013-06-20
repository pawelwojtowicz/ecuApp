#ifndef CONTROLLER_CCONTROLLERSTUB_H
#define CONTROLLER_CCONTROLLERSTUB_H

#include <Runtime/CStubBase.h> 

namespace Runtime
{
class CMessenger;
}

namespace Controller
{

class CControllerStub: public Runtime::CStubBase
{
public:
	CControllerStub( Runtime::IMessenger& rMessenger );
	virtual ~CControllerStub();

	virtual bool Initialize();
	virtual bool Shutdown();

	virtual void HandleMessage(Runtime::CMessage& rMessage);



private:
};

}
#endif //CONTROLLER_CONTROLLERSTUB_H
