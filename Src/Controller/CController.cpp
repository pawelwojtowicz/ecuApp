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
	m_controllerStub.Initialize();
	if ( m_messenger.SubscribeMessage( OWN_QUEUE_ID, msgId_Runtime_Timer_1000, &m_timerManager) )
	{
		InitializeTimer();
	}

}


Int32 CController::Run()
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

}
