#include "CController.h"
#include "Logger/Logger.h"
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
, m_deviceState(eWaitingForInit)
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
			RETAILMSG(ERROR, ("No configuration for Watchdog available. "));
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
			RETAILMSG(ERROR, ("No configuration for Process Controller available. Critical failure"));
		}
	}
	else
	{
		RETAILMSG(ERROR, ("Configuration file: [%s] is missing - Critical failure", completeConfigPath.c_str()));
	}

	m_controllerStub.Initialize(this);

	if ( m_messenger.SubscribeMessage( OWN_QUEUE_ID, msgId_Runtime_Timer_1000, &m_timerManager) )
	{
		InitializeTimer();
		m_pendingShutdownTimerId = GetTimerManager().CreateTimer(this);
		GetTimerManager().SetTimer(m_pendingShutdownTimerId, 5,0);
		m_deviceShutdownTimerId  = GetTimerManager().CreateTimer(this);
		GetTimerManager().SetTimer(m_deviceShutdownTimerId, 1,3);
	}
	m_deviceState = eOperation;
}


Int32 CController::Run()
{
	m_messenger.StartMsgProcessor();

	 return 0;
}

	//called right before shutdown - release all the resources here
void CController::Shutdown()
{
	m_watchdogManager.Shutdown();
	m_loggingAgent.Shutdown();
	m_loggerManager.Shutdown();

}

void CController::NotifyTimer()
{
	m_messenger.PostMessage(m_timerMessage);
}

void CController::NotifyTimer( const Int32& timerId )
{
	if ( timerId == m_pendingShutdownTimerId)
	{
		RETAILMSG(WARNING, ("Pending Shutdown timeout elapsed - shutting down device"));
		m_deviceState = eShutdown;
		m_processManager.SwitchOffProcessHandlers();
		m_controllerStub.BroadcastShutdown();
		GetTimerManager().StartTimer(m_deviceShutdownTimerId);
	}
	else if ( timerId == m_deviceShutdownTimerId )
	{
		RETAILMSG(INFO, ("Checking if process manager is ready to shutdown"));
		if ( m_processManager.Stopped() )
		{
			RETAILMSG(INFO, ("Stopping message processor"));
			m_messenger.StopMsgProcessor();
		}
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
	RETAILMSG(INFO, ("Received shutdown request"));
	if ( eOperation == m_deviceState )
	{
		RETAILMSG(INFO, ("Device is in Operation"));
		if ( m_processManager.IsBusy() )
		{
			RETAILMSG(INFO, ("ProcessManager is Busy - pending shutdown"));
			m_deviceState = ePendingShutdown;
			m_controllerStub.BroadcastPendingShutdown();
			GetTimerManager().StartTimer(m_pendingShutdownTimerId);
		}
		else
		{
			RETAILMSG(INFO, ("ProcessManager is iddle - immediate shutdown"));
			m_deviceState = eShutdown;
			m_processManager.SwitchOffProcessHandlers();
			m_controllerStub.BroadcastShutdown();
			GetTimerManager().StartTimer(m_deviceShutdownTimerId);
		}
	}
}

void CController::NotifyRestartRequest()
{
}

}
