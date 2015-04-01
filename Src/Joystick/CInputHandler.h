#ifndef CJOYSTICK_CInputHandler_H
#define CJOYSTICK_CInputHandler_H

#include <UCL/CThread.h>
#include <SDL/SDL_joystick.h>

namespace Joystick
{
class CInputHandler : public UCL::CThread
{
public:
	CInputHandler();
	virtual ~CInputHandler();
	
	void Initialize();
	void Shutdown();
	
private:
	virtual void Run();

private:
	bool m_running;
	
	SDL_Joystick* m_pJoystick;
};
}

#endif
