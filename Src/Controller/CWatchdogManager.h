#ifndef CONTROLLER_CWATCHDOGMANAGER_H
#define CONTROLLER_CWATCHDOGMANAGER_H

#include <Runtime/ITimerListener.h>

namespace Configuration
{
class CConfigNode;
}

namespace Runtime
{
class ITimerManager;
}

namespace Controller
{
class CWatchdogManager: public Runtime::ITimerListener
{
public:
	CWatchdogManager(Runtime::ITimerManager& rTimerManager);
	virtual ~CWatchdogManager();

	bool Initialize( const Configuration::CConfigNode* configNode );
	void Shutdown();

	virtual void NotifyTimer( const Int32& timerId );

private:
	CWatchdogManager(const CWatchdogManager&);
	CWatchdogManager& operator=(const CWatchdogManager&);

	Runtime::ITimerManager& m_rTimerManager;

	std::string m_watchdogDeviceName;

	UInt32 m_watchdogResetPeriod;

	Int32 m_watchdogExpirationTimeout;

	Int32 m_watchdogResetTimerId;

	int m_watchdogFD;
};
}
#endif //
