#include "CControllerStub.h"
#include "ControllerInterfaceConst.h"

namespace Controller
{
CControllerStub::CControllerStub(Runtime::IMessenger& rMessenger)
: Runtime::CStubBase(rMessenger, s_ControllerQueueName)
{
}

CControllerStub::~CControllerStub()
{
}

}
