#include "CInputHandler.h"
#include <Logger/Logger.h>
#include <SDL/SDL.h>


namespace Joystick
{
CInputHandler::CInputHandler()
: m_running(false)
, m_pJoystick(0)
{
}

CInputHandler::~CInputHandler()
{
}

void CInputHandler::Initialize()
{
	RETAILMSG(INFO, ("CInputHandler::Initialize()"));
	
	if ( SDL_Init( SDL_INIT_JOYSTICK) < 0)
	{
		RETAILMSG(INFO, ("Failed to initialize the SDL library"));	
	}

	if ( SDL_NumJoysticks() > 0 )
	{
		RETAILMSG(INFO, ("CInputHandler::Initialize() 1 "));
		m_pJoystick = SDL_JoystickOpen(0);
		
		if ( 0 != m_pJoystick )
		{
			RETAILMSG(INFO, ("CInputHandler::Initialize() 2 "));

			SDL_JoystickName(0);
			SDL_JoystickNumAxes(m_pJoystick);
			SDL_JoystickNumButtons(m_pJoystick);
			SDL_JoystickNumHats(m_pJoystick);
		}
	}
	
}

void CInputHandler::Shutdown()
{
	m_running = false;
	
	SDL_JoystickClose(m_pJoystick);
}

void CInputHandler::Run()
{
	m_running = true;
	
	while(m_running)
	{
		SDL_JoystickUpdate();
		
		Int16 axis = SDL_JoystickGetAxis(m_pJoystick,0);
		UInt8 button = SDL_JoystickGetButton(m_pJoystick,0);
		UInt8 hat = SDL_JoystickGetHat(m_pJoystick,0);
	}
}

}
