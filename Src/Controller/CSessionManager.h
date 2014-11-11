#ifndef CONTROLLER_CSESSIONMANAGER_H
#define CONTROLLER_CSESSIONMANAGER_H
#include <GlobalTypes.h>
#include "ISessionManager.h"
#include "ISessionStateListener.h"
#include <Runtime/ITimerManager.h>
#include <Runtime/ITimerListener.h>
#include <stdio.h>

namespace Controller
{
class CSessionManager	:	public ISessionManager
											, public Runtime::ITimerListener
{
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
	
	class BusyChecker
	{
	public:
		BusyChecker()
		: m_busy(false)
		, i(123)
		{
			printf("Tworzy sie nowe\n");
		}
		
		void operator()( tSessionItemMap::value_type& itemPair)
		{
			++i;
			printf("m_busy=%d, current=%d\n", m_busy, i );
			m_busy = m_busy || itemPair.second.SessionItemState;
		};
		
		bool IsBusy()
		{
			printf("returning busy %d\n", i);
			return m_busy;
		}
	private:
	int i;
		bool m_busy;
	};

	
public:
	CSessionManager(Runtime::ITimerManager& rTimerManager);
	virtual ~CSessionManager();
	
	bool Initialize();
	
	void Shutdown();
	
	void NotifySessionStateListeners(const tSessionState sessionState );
	
	bool IsBusy();

private:
	//Implementation of ISessionManager
	virtual Int32 RegisterSessionListener( ISessionStateListener* pListener );
	virtual void ReportItemState(const Int32& itemId,const bool busy );
private:
	// Runtime::ITimerListener implementation */
	virtual void NotifyTimer( const Int32& timerId );
	
private:
	// timers manager
	Runtime::ITimerManager& m_rTimerManager;
	
	// the variable used during assigning the item ids.
	Int32 m_currentItemId;
	
	//timerIds
	Int32 m_init1TimerId;
	Int32 m_init2TimerId;
	Int32 m_init3TimerId;
	Int32 m_pendingShutdownTimerId;


	tSessionItemMap m_items;	
};
}

#endif //CONTROLLER_CSESSIONMANAGER_H
