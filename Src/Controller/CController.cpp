#include "CController.h"
#include "Logger/Logger.h"
#include "Runtime/CMessage.h"
#include <UCL/SystemEnvironment.h>
#include <ControllerInterface/ControllerInterfaceConst.h>
#include <Configuration/CConfiguration.h>

#include <unistd.h>
#include <linux/reboot.h>
#include <sys/reboot.h>

static const char sCfg_WatchdogConfig[] = {"Watchdog"};
static const char sCfg_ProcessManager[] = {"Processes"};
static const char sCfg_LoggerConfig[]		= {"Logger"};
static const char sCfg_SessionManagerCfg[] = {"SessionManagment"};

Controller::CController gs;

namespace Controller
{
CController::CController()
: CExecutable("Controller")
, m_deviceState(eWaitingForInit)
, m_loggerManager()
, m_loggingAgent(s_ControllerQueueName)
, m_messenger()
, m_timerManager()
, m_timerMessage(0)
, m_controllerStub( m_messenger )
, m_sessionManager( m_timerManager )
, m_watchdogManager(m_timerManager)
, m_processManager( m_timerManager, m_sessionManager, m_controllerStub )
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
		// do the logger initialization first
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
		
		const Configuration::CConfigNode* pSessionMngmtCfg = pConfig->GetConfigNode(sCfg_SessionManagerCfg);
		if ( 0!= pSessionMngmtCfg )
		{
			m_sessionManager.Initialize(pSessionMngmtCfg);
			ISessionManager& sessionManagerRegisterer(m_sessionManager);
			sessionManagerRegisterer.RegisterSessionListener(this);
		}
		else
		{
			RETAILMSG(ERROR, ("No configuration for SessionManager available. "));
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
	
	//reboot command
	reboot( LINUX_REBOOT_CMD_POWER_OFF );
}

void CController::NotifyTimer()
{
	m_messenger.PostMessage(m_timerMessage);
}

void CController::NotifyTimer( const Int32& timerId )
{
}

void CController::NotifyUnitInitialized( const UInt32& unitId, const std::string& processQueue, const std::string& unitVersion)
{
	m_processManager.NotifyUnitInitialized(	unitId,processQueue,unitVersion);
}

void CController::NotifyUnitHeartbeat(	const UInt32 unitId, const Controller::tProcessStatus& status )
{
	m_processManager.NotifyUnitHeartbeat(	unitId, status );
}


void CController::NotifyShutdownRequest()
{
	m_sessionManager.ShutdownRequest();
}

void CController::NotifyRestartRequest()
{
}

void CController::ShutdownIfReady()
{
}

bool CController::NotifySessionState(const tSessionState sessionState)
{
	switch( sessionState )
	{
	case eSessionState_PendingShutdown:
		{
			RETAILMSG(INFO, ("Broadcast Pending Shutdown Message."))			
			m_controllerStub.BroadcastPendingShutdown();
		};break;

	case eSessionState_Shutdown:
		{
			RETAILMSG(INFO, ("Broadcast Shutdown Message."))			
			m_controllerStub.BroadcastShutdown();
		};break;
	case eSessionState_PowerOff:
		{
			RETAILMSG(INFO, ("Stopping message processor."))
			m_messenger.StopMsgProcessor();
		};break;
	default:;
	}

	return false;
}


}
