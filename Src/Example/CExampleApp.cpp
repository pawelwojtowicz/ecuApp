#include "CExampleApp.h"
#include <Logger/Logger.h>


// important - global instance of the new class
ExampleApp::CExampleApp gs;

namespace ExampleApp
{

CExampleApp::CExampleApp()
//important - queue name of the unit must start with the /
: Runtime::CRuntimeUnit("ExampleApp", "/ExQueue")
, m_timer1Id(0)
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



  // prepare some test timer, ( started after 5 seconds, triggered every 2seconds afterwards
  m_timer1Id = GetTimerManager().CreateTimer(this);
  GetTimerManager().SetTimer(m_timer1Id, 5, 2 );
  GetTimerManager().StartTimer(m_timer1Id);

  InitDone(true);
}

void CExampleApp::NotifyTimer( const Int32& timerId )
{
  if (timerId == m_timer1Id)
  {
    RETAILMSG(INFO, ("Test timer"));
  }
}


}
