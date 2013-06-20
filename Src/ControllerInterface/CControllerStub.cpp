#include "CControllerStub.h"
#include "ControllerInterfaceConst.h"
#include "Runtime/CMessenger.h"

namespace Controller
{
CControllerStub::CControllerStub(Runtime::IMessenger& rMessenger)
: Runtime::CStubBase(rMessenger, s_ControllerQueueName)
{
}

CControllerStub::~CControllerStub()
{
}

bool CControllerStub::Initialize()
{
	bool retVal(Runtime::CStubBase::Initialize());
	return retVal;
}

bool CControllerStub::Shutdown()
{
	bool retVal(Runtime::CStubBase::Shutdown());

	return retVal;
}

void CControllerStub::HandleMessage(Runtime::CMessage& rMessage)
{
}


}
