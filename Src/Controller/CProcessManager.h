#ifndef CONTROLLER_CPROCESSMANAGER_H
#define CONTROLLER_CPROCESSMANAGER_H
#include <Runtime/ITimerManager.h>
#include <Runtime/ITimerListener.h>

namespace Configuration
{
	class CConfigNode;
}

namespace Controller
{
class CProcessManager : public Runtime::ITimerListener
{
public:
	CProcessManager( Runtime::ITimerManager& rTimerManager );
	virtual ~CProcessManager();

	bool Initialize( const Configuration::CConfigNode* configNode );
	void Shutdown();

	/** Runtime::ITimerListener implementation */
	virtual void NotifyTimer( const Int32& timerId );

private:
	CProcessManager(const CProcessManager&);
	CProcessManager& operator=(const CProcessManager&);

	Runtime::ITimerManager& m_rTimerManager;

	Int32 m_processMonitorTimerId;

	UInt32 m_processMonitorInterval;
};
}

#endif
