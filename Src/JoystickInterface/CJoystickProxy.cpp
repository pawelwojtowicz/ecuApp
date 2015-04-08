#include "CJoystickProxy.h"
#include <Runtime/IMessenger.h>
#include <Runtime/CMessage.h>
#include "JoystickInterfaceConst.h"
#include "CJoyState.h"

namespace Joystick
{
CJoystickProxy::CJoystickProxy(Runtime::IMessenger& rMessenger)
: Runtime::CProxyBase(rMessenger, s_JoystickQueueName)
, m_sharedStorage()
{
}

CJoystickProxy::~CJoystickProxy()
{
}

bool CJoystickProxy::Initialize()
{
	bool retVal(CProxyBase::Initialize());
	
	CJoyState initialState;
	initialState.SetAxisCount(5);
	initialState.SetCrossCount(5);
	initialState.SetButtonCount(15);
	
	retVal &= m_sharedStorage.Initialize(s_JoystickStorage, initialState.GetStorageSize(),false);

	return retVal;
}

bool CJoystickProxy::GetJoystickState( CJoyState& joystate)
{
	return m_sharedStorage.GetData(joystate);
}

}
