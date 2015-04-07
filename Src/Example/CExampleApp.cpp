#include "CExampleApp.h"
#include <Logger/Logger.h>
#include <ControllerInterface/CPublicProcessInfo.h>


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
  GetTimerManager().SetTimer(m_shutdownTimer, 20, 0 );
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
    RETAILMSG(INFO, ("Test timer"));
    m_ttsProxy.Say("Test");
    Controller::CPublicProcessInfo processInfo;
    GetControllerProxy().GetCurrentProcessInfo(processInfo);
    
    Controller::CPublicProcessInfo::tPublicProcessInfoList list = processInfo.GetProcessInfo();
    
    for ( Controller::CPublicProcessInfo::tPublicProcessInfoIter 	iter = list.begin() ; 
    																															iter != list.end() ; 
    																															++iter)
    {
    	    RETAILMSG(INFO, ("id=[%d] name=[%s] version=[%s] status=[%d]"	, iter->ProcessID
  	 	    																																, iter->ProcessName.c_str()
  		    																																, iter->VersionInformation.c_str()
  		    																																, iter->UnitState));
    }
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
