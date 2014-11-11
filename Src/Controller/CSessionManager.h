#ifndef CONTROLLER_CSESSIONMANAGER_H
#define CONTROLLER_CSESSIONMANAGER_H
#include <GlobalTypes.h>
#include "ISessionManager.h"
#include <Runtime/ITimerManager.h>
#include <Runtime/ITimerListener.h>


namespace Controller
{
class ISessionStateListener;

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
	
public:
	CSessionManager(Runtime::ITimerManager& rTimerManager);
	virtual ~CSessionManager();
	
	bool Initialize();
	
	void Shutdown();

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
