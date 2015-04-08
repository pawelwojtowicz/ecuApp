#ifndef JOYSTICK_CJoystickProxy_H
#define JOYSTICK_CJoystickProxy_H
#include <Runtime/CProxyBase.h>
#include <Runtime/CSharedStorage.h>


namespace Joystick
{
class CJoyState;

class CJoystickProxy : public Runtime::CProxyBase
{
public:
	CJoystickProxy(Runtime::IMessenger& rMessenger);
	virtual ~CJoystickProxy();

	bool Initialize();

	bool GetJoystickState( CJoyState& joystate);

private:
	CJoystickProxy(const CJoystickProxy&);
	CJoystickProxy& operator=(const CJoystickProxy&);
	
	Runtime::CSharedStorage m_sharedStorage;
};

}

#endif
