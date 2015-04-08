#ifndef Joystick_CJoystickStub_H
#define Joystick_CJoystickStub_H

#include <Runtime/CStubBase.h> 
#include <Runtime/CSharedStorage.h>

namespace Runtime
{
class CMessenger;
}

namespace Joystick
{
class CJoyState;

class CJoystickStub: public Runtime::CStubBase
{
public:
	CJoystickStub( Runtime::IMessenger& rMessenger );
	virtual ~CJoystickStub();

	bool InitializeJoystickStorage( );
	
	bool UpdateJoysticState( CJoyState& state);
private:
	CJoystickStub(const CJoystickStub&);
	CJoystickStub& operator= ( const CJoystickStub&);

private:	
	Runtime::CSharedStorage m_sharedStorage;
};

}
#endif //CONTROLLER_CONTROLLERSTUB_H
