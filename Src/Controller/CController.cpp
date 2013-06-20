#include "CController.h"
#include "Runtime/CMessage.h"
#include <Configuration/CConfiguration.h>

Controller::CController gs;

namespace Controller
{
CController::CController()
: CExecutable("Controller")
, m_messenger()
, m_timerMessage(0)
, m_controllerStub( m_messenger )
{
	m_timerMessage.SetMessageId(msgId_Runtime_Timer_1000);
	m_timerMessage.SetMsgPrio(255);
	m_timerMessage.SetTargetId(OWN_QUEUE_ID);
}


void CController::Initialize()
{
	const Configuration::CConfigNode* pConfig = Configuration::CConfiguration::GetConfiguration("//home//tpdev//Programowanie//lnxEmbdDevice//Configuration//Configuration.xml");

	if (pConfig != 0 )
	{
		printf("OK\n");

	}
	else
	{
		printf("NOK\n");
	}

	m_controllerStub.Initialize();

  m_timer1Id = ( GetTimerManager().CreateTimer(this) );
  m_timer2Id = ( GetTimerManager().CreateTimer(this) );

	GetTimerManager().SetTimer(m_timer1Id, 5,2);
	GetTimerManager().SetTimer(m_timer2Id, 10,0);
	
	GetTimerManager().StartTimer(m_timer1Id);
	GetTimerManager().StartTimer(m_timer2Id);

	if ( m_messenger.SubscribeMessage( OWN_QUEUE_ID, msgId_Runtime_Timer_1000, &m_timerManager) )
	{
		InitializeTimer();
	}
}


Int32 CController::Run()
{
	m_messenger.StartMsgProcessor();

	 return 0;
}

	//called right before shutdown - release all the resources here
void CController::Shutdown()
{

}

void CController::NotifyTimer()
{
	m_messenger.PostMessage(m_timerMessage);
}

void CController::NotifyTimer( const Int32& timerId )
{
	if (timerId == m_timer1Id )
	{
		printf("m_timer1Id jedzie co 2s\n");
	}
	else if (m_timer2Id == timerId)
	{
		printf("m_timer2Id jedzie raz po 10s\n");
	}
}

}
