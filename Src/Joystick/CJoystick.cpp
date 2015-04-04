#include "CJoystick.h"

// important - global instance of the new class
Joystick::CJoystick gs;

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
	// important - initialize the messenger
  CRuntimeUnit::Initialize();
  
	m_handler.Initialize();
	
	InitDone(true);
}

void CJoystick::Shutdown()
{
	m_handler.Shutdown();
}

}
