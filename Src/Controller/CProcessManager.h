#ifndef CONTROLLER_CPROCESSMANAGER_H
#define CONTROLLER_CPROCESSMANAGER_H
#include <map>
#include <ControllerInterface/ControllerInterfaceConst.h>
#include <Runtime/ITimerManager.h>
#include <Runtime/ITimerListener.h>


namespace Configuration
{
	class CConfigNode;
}

namespace Controller
{
class CProcessHandler;

class CProcessManager : public Runtime::ITimerListener
{
	typedef std::map< UInt32, CProcessHandler* > tProcessMap;
	typedef tProcessMap::iterator tProcessIterator;
public:
	CProcessManager( Runtime::ITimerManager& rTimerManager );
	virtual ~CProcessManager();

	bool Initialize( const Configuration::CConfigNode* configNode );
	void Shutdown();

	void NotifyUnitInitialized(	const UInt32& unitId, 
															const std::string& processQueue, 
															const std::string& unitVersion);
	void NotifyUnitHeartbeat(	const UInt32 unitId, 
														const tProcessStatus& status );

	/** Runtime::ITimerListener implementation */
	virtual void NotifyTimer( const Int32& timerId );

private:
	CProcessManager(const CProcessManager&);
	CProcessManager& operator=(const CProcessManager&);

	tProcessMap m_processList;

	Runtime::ITimerManager& m_rTimerManager;

	Int32 m_processMonitorTimerId;

	UInt32 m_processMonitorInterval;
};
}

#endif
