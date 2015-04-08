#include "CJoystick.h"
#include <JoystickInterface/JoystickInterfaceConst.h>

// important - global instance of the new class
Joystick::CJoystick gs;

namespace Joystick
{
CJoystick::CJoystick()
: Runtime::CRuntimeUnit("Joystick", s_JoystickQueueName )
, m_joystickStub(GetMessenger())
, m_handler(m_joystickStub)
{
}

CJoystick::~CJoystick()
{
}

void CJoystick::Initialize()
{
	// important - initialize the messenger
  CRuntimeUnit::Initialize();
  
  m_joystickStub.Initialize();
  
	m_handler.Initialize();
	
	InitDone(true);
}

void CJoystick::Shutdown()
{
	m_handler.Shutdown();
	
	m_joystickStub.Shutdown();
}

}
