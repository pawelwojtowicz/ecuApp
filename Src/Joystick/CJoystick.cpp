#include "CJoystick.h"

namespace Joystick
{
CJoystick::CJoystick()
: Runtime::CRuntimeUnit("Joystick", "joystickQ")
{
}

CJoystick::~CJoystick()
{
}

void CJoystick::Initialize()
{
	m_handler.Initialize();
}

void CJoystick::Shutdown()
{
	m_handler.Shutdown();
}

}
