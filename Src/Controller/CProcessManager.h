#ifndef CONTROLLER_CPROCESSMANAGER_H
#define CONTROLLER_CPROCESSMANAGER_H
#include <map>
#include <ControllerInterface/ControllerTypes.h>
#include <Runtime/ITimerManager.h>
#include <Runtime/ITimerListener.h>
#include <Controller/ISessionStateListener.h>


namespace Configuration
{
	class CConfigNode;
}

namespace Controller
{

class CProcessInfo;
class ISessionManager;
class IProcessControl;
class IProcessStatusReporter;

class CProcessManager : public Runtime::ITimerListener
											, public Controller::ISessionStateListener
{
	typedef std::map< UInt32, CProcessInfo* > tProcessInfoMap;
	typedef tProcessInfoMap::iterator tProcessIterator;

public:
	CProcessManager(Runtime::ITimerManager& rTimerManager, 
									ISessionManager& rSessionManager,
									IProcessStatusReporter& rControllerStub,
									IProcessControl* pProcessControl = 0 );
									
	virtual ~CProcessManager();

	bool Initialize( const Configuration::CConfigNode* configNode, const UInt32& defaultDebugZones );
	
	void Shutdown();

	void GetRuntimeUnitShortnameList( tStringVector& runtimrShortnameList);

public:

	void NotifyUnitInitialized(	const UInt32& unitId, 
															const std::string& processQueue, 
															const std::string& unitVersion);
	void NotifyUnitHeartbeat(	const UInt32 unitId, 
														const tProcessStatus& status );
														
private:
	/** Controller::ISessionStateListener implementation */
	virtual bool NotifySessionState(const tSessionState sessionState);
	
	/** Runtime::ITimerListener implementation */
	virtual void NotifyTimer( const Int32& timerId );
	
private:
	/** returns aggregated status of all controlled processes */
	bool CheckProcessManagerState();
	
	void PublishProcessInfo();

private:
	CProcessManager(const CProcessManager&);
	CProcessManager& operator=(const CProcessManager&);
	
	/** Session Manager interface */
	ISessionManager& m_sessionManager;
	
	/** Timers manager */
	Runtime::ITimerManager& m_rTimerManager;
	
	IProcessStatusReporter& m_rControllerStub;
	
	/** Process */
	IProcessControl* m_processControl;

	/** list of process info structures */
	tProcessInfoMap m_processList;

	/** timerID for the process monitor interval */
	Int32 m_processMonitorTimerId;

	/** process monitor interval*/
	UInt32 m_processMonitorInterval;
	
	/** the Id, that will be assigned, when the process manager registers for the session
		* notifications. Used for reporting to CSessionManager*/
	Int32 m_sessionItemId;
	
	/** the flag indicates whether the PC was injected. We won't clean it up, if so*/
	bool m_processControlInjected;
};
}

#endif
