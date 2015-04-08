#include "CInputHandler.h"
#include <Logger/Logger.h>
#include <SDL/SDL.h>
#include <JoystickInterface/CJoyState.h>
#include <JoystickInterface/CJoystickStub.h>

#include <unistd.h>


namespace Joystick
{
CInputHandler::CInputHandler(CJoystickStub& stub)
: m_running(false)
, m_pJoystick(0)
, m_axisCount(0)
, m_crossCount(0)
, m_buttonCount(0)
, m_rJoystickStub(stub)
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
		m_pJoystick = SDL_JoystickOpen(0);
		
		if ( 0 != m_pJoystick )
		{
			std::string joystickName(SDL_JoystickName(0));
			m_axisCount 	= SDL_JoystickNumAxes(m_pJoystick);
			m_buttonCount = SDL_JoystickNumButtons(m_pJoystick);
			m_crossCount 	= SDL_JoystickNumHats(m_pJoystick);
			
			RETAILMSG(INFO, ("Joystick name=[%s] detected. AxesCount=[%d], ButtonCount=[%d], CrossCount=[%d]"
												, joystickName.c_str(), m_axisCount , m_buttonCount , m_crossCount));
				// start the polling
			Start();

		}
	}
	else
	{
		RETAILMSG(ERROR, ("No Joysticks Attached to the computer"))
	}
	
}

void CInputHandler::Shutdown()
{
	m_running = false;
	
	WaitFor();
	
	SDL_JoystickClose(m_pJoystick);
}

void CInputHandler::Run()
{
	m_running = true;
	
	CJoyState joyState;
	
	joyState.SetAxisCount(m_axisCount);
	joyState.SetCrossCount( m_crossCount );
	joyState.SetButtonCount( m_buttonCount);
	
	while(m_running)
	{
		SDL_JoystickUpdate( );
		
		for (UInt8 i = 0 ; i < m_axisCount ; ++i )
		{
			joyState.SetAxis(i , SDL_JoystickGetAxis(m_pJoystick,i) );
		}
		
		for (UInt8 i = 0 ; i < m_buttonCount ; ++i )
		{
			joyState.SetButtonState(i , SDL_JoystickGetButton(m_pJoystick,i) );
		}
		
		for (UInt8 i = 0 ; i < m_crossCount ; ++i )
		{
			UInt8 crossState(SDL_JoystickGetHat(m_pJoystick,i));
			
			joyState.SetCrossState(i , crossState );
		}
		
		m_rJoystickStub.UpdateJoysticState(joyState);
		
		usleep( 100 * 1000 ); // wait 100ms with the next update
		
		
	}
}

}
