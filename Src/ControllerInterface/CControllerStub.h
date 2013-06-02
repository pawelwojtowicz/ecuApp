#ifndef CONTROLLER_CCONTROLLERSTUB_H
#define CONTROLLER_CCONTROLLERSTUB_H

#include <Runtime/CStubBase.h> 

namespace Controller
{

class CControllerStub: public Runtime::CStubBase
{
public:
	CControllerStub( Runtime::IMessenger& rMessenger );
	virtual ~CControllerStub();


private:
};

}
#endif //CONTROLLER_CONTROLLERSTUB_H
