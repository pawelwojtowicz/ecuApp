#ifndef CONTROLLER_CSESSIONMANAGER_H
#define CONTROLLER_CSESSIONMANAGER_H
#include <GlobalTypes.h>
#include "ISessionManager.h"
#include "ISessionStateListener.h"
#include <Runtime/ITimerManager.h>
#include <Runtime/ITimerListener.h>
#include <stdio.h>

namespace Configuration
{
class CConfigNode;
}

namespace Controller
{
class CSessionManager	:	public ISessionManager
											, public Runtime::ITimerListener
{
	typedef enum
	{
		eEvent_PhaseCompleted,
		eEvent_TimeoutElapsed,
		eEvent_ShutdownRequest
	} tSessionEvents;
	
	struct SessionItem
	{
		ISessionStateListener* pSessionStateListener;
		bool SessionItemState;
	};
	
	typedef std::map<Int32, SessionItem> tSessionItemMap;
	typedef tSessionItemMap::iterator tSessionItemIterator;	
	
	class NotifyAndUpdateItemState
	{
	public:
		NotifyAndUpdateItemState(const tSessionState& sessionState)
		: m_currentSessionState(sessionState)
		{
		}
		
		void operator()( tSessionItemMap::value_type& itemPair)
		{
			itemPair.second.SessionItemState = itemPair.second.pSessionStateListener->NotifySessionState(m_currentSessionState);
		};
	
		tSessionState m_currentSessionState;
	};
	
public:
	CSessionManager(Runtime::ITimerManager& rTimerManager);
	virtual ~CSessionManager();
	
	bool Initialize(const Configuration::CConfigNode* pConfigNode);
	
	void Shutdown();
	
	void NotifySessionStateListeners(const tSessionState sessionState );
	
	bool IsBusy();
	
	void ShutdownRequest();

private:
	//Implementation of ISessionManager
	virtual Int32 RegisterSessionListener( ISessionStateListener* pListener );
	virtual void ReportItemState(const Int32& itemId,const bool busy );
private:
	// Runtime::ITimerListener implementation */
	virtual void NotifyTimer( const Int32& timerId );
	
private:
	//Tooling Clases
	void DispatchSessionEvent(tSessionEvents event);
	
	tSessionState EvaluateNextState( const tSessionEvents event );
	
	UInt32 GetPhaseTimeout(tSessionState sessionState);
	
private:
	// timers manager
	Runtime::ITimerManager& m_rTimerManager;
	
	// the variable used during assigning the item ids.
	Int32 m_currentItemId;
	
	//timerIds
	Int32 m_timeoutTimerId;
	
	//timeout values
	UInt32 m_init1Timeout;
	UInt32 m_init2Timeout;
	UInt32 m_init3Timeout;
	UInt32 m_pendingShutdownTimeout;
	UInt32 m_shutdownTimeout;

	tSessionItemMap m_items;
	
	tSessionState m_currentSessionState;	
};
}

#endif //CONTROLLER_CSESSIONMANAGER_H
