#ifndef CJOYSTICK_CInputHandler_H
#define CJOYSTICK_CInputHandler_H
#include <GlobalTypes.h>
#include <UCL/CThread.h>
#include <SDL/SDL_joystick.h>

namespace Joystick
{
class CJoystickStub;

class CInputHandler : public UCL::CThread
{
public:
	CInputHandler( CJoystickStub& stub);
	virtual ~CInputHandler();
	
	void Initialize();
	void Shutdown();
	
private:
	virtual void Run();

private:
	bool m_running;	
	SDL_Joystick* m_pJoystick;
	
	UInt8 m_axisCount;
	UInt8 m_crossCount;
	UInt8 m_buttonCount;
	
	CJoystickStub& m_rJoystickStub;
};
}

#endif
