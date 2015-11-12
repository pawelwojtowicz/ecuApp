#include "CWatchdogManager.h"
#include <Logger/Logger.h>
#include <linux/watchdog.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <getopt.h>
#include <fcntl.h>
#include <Configuration/CConfiguration.h>
#include <Runtime/CTimerManager.h>
#include <stdio.h>

static const char sCfg_DeviceIdParName[] 					= {"DeviceId"};
static const char sCfg_WatchdogRefreshPeriod[] 		= {"WatchdogRefreshPeriod"};
static const char sCfg_WatchdogExpirationTimeout[]= {"WatchdogExpirationTimeout"};

static const char 	sDflt_DeviceName[] 					= {"Dupa:"};
static const UInt8 	sDflt_WatchdogResetPeriod 	= 5;
static const UInt8 	sDflt_MaxWatchdogCounter 		= 10;

namespace Controller
{

CWatchdogManager::CWatchdogManager(Runtime::ITimerManager& rTimerManager)
: m_rTimerManager(rTimerManager)
, m_watchdogDeviceName(sDflt_DeviceName)
,	m_watchdogResetPeriod(sDflt_WatchdogResetPeriod)
, m_watchdogExpirationTimeout(sDflt_MaxWatchdogCounter)
, m_watchdogResetTimerId(0)
, m_watchdogFD(-1)
{
}

CWatchdogManager::~CWatchdogManager()
{
}

bool CWatchdogManager::Initialize( const Configuration::CConfigNode* configNode )
{
	bool retVal(false);

	if ( 0 != configNode )
	{
		m_watchdogDeviceName = configNode->GetParameter(sCfg_DeviceIdParName)->GetString(m_watchdogDeviceName);
		
		m_watchdogResetPeriod = configNode->GetParameter(sCfg_WatchdogRefreshPeriod)->GetUInt32(m_watchdogResetPeriod);

		m_watchdogExpirationTimeout = configNode->GetParameter(sCfg_WatchdogExpirationTimeout)->GetUInt32(m_watchdogExpirationTimeout);

		RETAILMSG(INFO, ("Watchdog configuration: deviceName=[%s], watchdogExp=[%d], refreshPeriod=[%d]",
											 m_watchdogDeviceName.c_str(),
											 m_watchdogExpirationTimeout, 
											 m_watchdogResetPeriod));

		// initialize the watchdog driver
		m_watchdogFD = open(m_watchdogDeviceName.c_str(), O_RDWR);
		if ( -1 != m_watchdogFD )
		{
			ioctl(m_watchdogFD, WDIOC_SETTIMEOUT, &m_watchdogExpirationTimeout);
			ioctl(m_watchdogFD, WDIOC_KEEPALIVE, NULL);
		}
		else
		{
			RETAILMSG(ERROR, ("Failed to open watchdog device [%s]", m_watchdogDeviceName.c_str() ));
		}

#pragma message ("Add reporting last restart reason")

		// initialize the timers
		m_watchdogResetTimerId = m_rTimerManager.CreateTimer(this);
		if ( -1 != m_watchdogResetTimerId )
		{
			m_rTimerManager.SetTimer(m_watchdogResetTimerId,m_watchdogResetPeriod, m_watchdogResetPeriod);
			m_rTimerManager.StartTimer( m_watchdogResetTimerId );
		}	
	}

	return retVal;
}

void CWatchdogManager::Shutdown()
{
	RETAILMSG(INFO, ("Shutting down watchdog manager - device shuts down correctly"));
	if (-1 != m_watchdogFD )
	{
		// write V, which signalizes the application is being closed correctly
		write(m_watchdogFD, "V", 1);
		//close the watchdog driver
		close(m_watchdogFD);
	}
}

void CWatchdogManager::NotifyTimer( const Int32& timerId )
{
	if ( timerId == m_watchdogResetTimerId )
	{
		RETAILMSG(INFO, ("Resetting watchdog"));
		if ( -1 != m_watchdogFD )
		{
			ioctl(m_watchdogFD, WDIOC_KEEPALIVE, NULL);
		}
	}
}

}
