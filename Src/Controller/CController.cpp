#include "CController.h"
#include "Runtime/CMessage.h"
#include <UCL/SystemEnvironment.h>
#include <Configuration/CConfiguration.h>

static const char sCfg_WatchdogConfig[] = {"Watchdog"};
static const char sCfg_ProcessManager[] = {"ProcessManager"};
static const char sCfg_LoggerConfig[]		= {"Logger"};

Controller::CController gs;

namespace Controller
{
CController::CController()
: CExecutable("Controller")
, m_loggerManager()
, m_loggingAgent()
, m_messenger()
, m_timerMessage(0)
, m_controllerStub( m_messenger )
, m_watchdogManager(m_timerManager)
, m_processManager(m_timerManager)
{
	m_timerMessage.SetMessageId(msgId_Runtime_Timer_1000);
	m_timerMessage.SetMsgPrio(255);
	m_timerMessage.SetTargetId(OWN_QUEUE_ID);
}


void CController::Initialize()
{
	std::string completeConfigPath = UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Config, "ControllerConfig.xml");
	const Configuration::CConfigNode* pConfig = Configuration::CConfiguration::GetConfiguration(completeConfigPath);

	if (pConfig != 0 )
	{

		const Configuration::CConfigNode* pLoggerConfig = pConfig->GetConfigNode(sCfg_LoggerConfig);
		m_loggerManager.Initialize(pLoggerConfig);
		m_loggingAgent.Initialize(0);// okomentowac to
		m_loggingAgent.SetDebugLevel(m_loggerManager.GetDefaultDebugZones());

		

		const Configuration::CConfigNode* pWatchdogConfig = pConfig->GetConfigNode(sCfg_WatchdogConfig);
		if ( 0 != pWatchdogConfig )
		{
			m_watchdogManager.Initialize(pWatchdogConfig);
		}
		else
		{
			printf("failed to initialize Watchdog\n");
		}

		const Configuration::CConfigNode* pProcessMgrConfig = pConfig->GetConfigNode(sCfg_ProcessManager);
		if ( 0!= pProcessMgrConfig )
		{
			m_processManager.Initialize( pProcessMgrConfig, m_loggerManager.GetDefaultDebugZones() );
			tStringVector processShortnameList;
			m_processManager.GetRuntimeUnitShortnameList(processShortnameList);
			m_loggerManager.UpdateSourceDictionary(processShortnameList);
		}
		else
		{
			printf("failed to initialize the process controller");
		}
	}
	else
	{
		printf("Configuration file not found\n");
	}

	m_controllerStub.Initialize(this);

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
	m_loggerManager.Shutdown();

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

void CController::NotifyUnitInitialized(	const UInt32& unitId, 
																			const std::string& processQueue, 
																			const std::string& unitVersion)
{
	m_processManager.NotifyUnitInitialized(	unitId,processQueue,unitVersion);
}

void CController::NotifyUnitHeartbeat(	const UInt32 unitId, 
																		const Controller::tProcessStatus& status )
{
	m_processManager.NotifyUnitHeartbeat(	unitId, status );
}


void CController::NotifyShutdownRequest()
{
	static int a = 0;
	printf("Request Shutdown dostalema = [%d]\n", a);

	if ( a++%5 )
	{
		printf("Broadcast\n");
		m_controllerStub.BroadcastPendingShutdown();
	}

	if (a > 10)
	{
		m_controllerStub.BroadcastShutdown();
	}
}

void CController::NotifyRestartRequest()
{
}

}
