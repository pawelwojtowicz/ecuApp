#ifndef CONTROLLER_CPROCESSMANAGER_H
#define CONTROLLER_CPROCESSMANAGER_H
#include <map>
#include <ControllerInterface/ControllerTypes.h>
#include <Runtime/ITimerManager.h>
#include <Runtime/ITimerListener.h>
#include "CProcessHandler.h"


namespace Configuration
{
	class CConfigNode;
}

namespace Controller
{

class CProcessManager : public Runtime::ITimerListener
{
	typedef std::map< UInt32, CProcessHandler* > tProcessMap;
	typedef tProcessMap::iterator tProcessIterator;

	struct RuntimeUnitGroup
	{
		std::string GroupName;
		UInt32 GroupId;
	};
	typedef std::map< UInt32, RuntimeUnitGroup > tTimerToGroupMap;
	typedef tTimerToGroupMap::const_iterator tGroupIterator;
	
	class HasState
	{
	public:
		HasState(const tProcessStatus& value)
		: m_desiredUnitState(value)
		{
		};
		
		bool operator()(const tProcessMap::value_type& processPair) const
		{
			return ( m_desiredUnitState == processPair.second->GetUnitStatus() );
		};
	
	private:
		tProcessStatus m_desiredUnitState;
	};
	
	class DoesNotHaveState
	{
	public:
		DoesNotHaveState(const tProcessStatus& value)
		: m_desiredUnitState(value)
		{
		};
		
		bool operator()(const tProcessMap::value_type& processPair) const
		{
			return ( m_desiredUnitState != processPair.second->GetUnitStatus() );
		};
	
	private:
		tProcessStatus m_desiredUnitState;
	};
	
	class StopProcessHandler
	{
	public:
		void operator()(const tProcessMap::value_type& processPair)
		{
			processPair.second->StopProcessHandler();
		};
	};

public:
	CProcessManager( Runtime::ITimerManager& rTimerManager );
	virtual ~CProcessManager();

	bool Initialize( const Configuration::CConfigNode* configNode, const UInt32& defaultDebugZones );

	void GetRuntimeUnitShortnameList( tStringVector& runtimrShortnameList);

	bool IsBusy();

	bool Stopped();

	void SwitchOffProcessHandlers();

	void Shutdown();

public:

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

	tTimerToGroupMap m_timer2GroupMap;

	tProcessMap m_processList;

	Runtime::ITimerManager& m_rTimerManager;

	Int32 m_processMonitorTimerId;

	UInt32 m_processMonitorInterval;
};
}

#endif
