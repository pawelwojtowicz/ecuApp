#include "CJoystickStub.h"
#include <Runtime/CMessenger.h>
#include <UCL/CSerializable.h>
#include "CJoyState.h"
#include "JoystickInterfaceConst.h"

namespace Joystick
{
CJoystickStub::CJoystickStub(Runtime::IMessenger& rMessenger)
: Runtime::CStubBase(rMessenger, s_JoystickQueueName)
, m_sharedStorage()
{
}

CJoystickStub::~CJoystickStub()
{
}


bool CJoystickStub::InitializeJoystickStorage( )
{
	CJoyState initialState;
	initialState.SetAxisCount(5);
	initialState.SetCrossCount(5);
	initialState.SetButtonCount(15);
	return m_sharedStorage.Initialize(s_JoystickStorage, initialState.GetStorageSize(),true);
}
	
bool CJoystickStub::UpdateJoysticState( CJoyState& state)
{
	return m_sharedStorage.SetData(state);
}

}
