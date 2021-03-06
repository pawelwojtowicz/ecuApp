#include "CExampleApp.h"
#include <Logger/Logger.h>
#include <ControllerInterface/CPublicProcessInfo.h>
#include <string.h>
#include <stdlib.h>


// important - global instance of the new class
ExampleApp::CExampleApp gs;

namespace ExampleApp
{

CExampleApp::CExampleApp()
//important - queue name of the unit must start with the /
: Runtime::CRuntimeUnit("ExampleApp", "ExQueue")
, m_timer1Id(0)
, m_shutdownTimer(0)
, m_ttsProxy(GetMessenger())
{
}

CExampleApp::~CExampleApp()
{
}

void CExampleApp::Initialize()
{
// important - initialize the messenger
  CRuntimeUnit::Initialize();

// important - initialize the timer manager
  InitializeTimerManager();

  m_ttsProxy.Initialize();
       


  // prepare some test timer, ( started after 5 seconds, triggered every 2seconds afterwards
  m_timer1Id = GetTimerManager().CreateTimer(this);
  GetTimerManager().SetTimer(m_timer1Id, 5, 2 );
  GetTimerManager().StartTimer(m_timer1Id);

  m_shutdownTimer = GetTimerManager().CreateTimer(this);
  GetTimerManager().SetTimer(m_shutdownTimer, 120, 0 );
  GetTimerManager().StartTimer(m_shutdownTimer);

  m_iddleTimer = GetTimerManager().CreateTimer(this);
  GetTimerManager().SetTimer(m_iddleTimer, 30, 0 );
  GetTimerManager().StartTimer(m_iddleTimer);
  SetBusy();

  InitDone(true);
}

void CExampleApp::NotifyTimer( const Int32& timerId )
{
  if (timerId == m_timer1Id)
  {
    m_ttsProxy.Say("Test");
  }
  else if ( timerId == m_shutdownTimer )
  {
    RETAILMSG(INFO, ("Requesting shutdown"));
    GetControllerProxy().RequestShutdown();
    m_ttsProxy.Say("Requesting Shutdown");
  }
  else if ( timerId ==m_iddleTimer )
  {
    RETAILMSG(INFO, ("ExampleApp iddle - system should be down in couple of seconds"));
    m_ttsProxy.Say("Example application reports iddle - system should be down in couple of seconds");
    SetIddle();
  }
}


}
