#include "CTimerManager.h"
#include "ITimerListener.h"
#include "CMessage.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

namespace Runtime
{
CTimerManager::CTimerManager()
:m_nextFreeTimerId(1)
{
}

CTimerManager::~CTimerManager()
{
}


Int32 CTimerManager::CreateTimer( ITimerListener* timerListener )
{
	Int32 timerId(-1);
	if ( 0 != timerListener )
	{ 
		tTimerStruct newTimerInfo;
		newTimerInfo.active = false;
		newTimerInfo.timerDelay = 0;
		newTimerInfo.timerPeriod = 0;
		newTimerInfo.timerNextExpiration = 0;
		newTimerInfo.timerSubscriber = timerListener;
		timerId = m_nextFreeTimerId++;
		m_timerInfoMap.insert(tTimerInfoMap::value_type( timerId,newTimerInfo ));

	}
	return timerId;
}

void CTimerManager::DisposeTimer(const Int32& timerId )
{
	tTimerInfoIterator timerIter = m_timerInfoMap.find(timerId);
	if (m_timerInfoMap.end() != timerIter )
	{
		m_timerInfoMap.erase(timerIter);
	}
}

bool CTimerManager::SetTimer( const Int32& timerId, const UInt32 delay, const UInt32 period)
{
	tTimerInfoIterator timerIter = m_timerInfoMap.find(timerId);
	if (m_timerInfoMap.end() != timerIter )
	{
		timerIter->second.timerDelay		= delay * 1000;
		timerIter->second.timerPeriod 	= period * 1000;
		return true;
	}
	return false;
}
	
bool CTimerManager::StartTimer(const Int32& timerId )
{
	tTimerInfoIterator timerIter = m_timerInfoMap.find(timerId);
	if (m_timerInfoMap.end() != timerIter )
	{
		UInt32 currentTime(GetCurrentTime());
		timerIter->second.active = true;
		if ( timerIter->second.timerDelay > 0 )
		{
			timerIter->second.timerNextExpiration = currentTime + timerIter->second.timerDelay;
		}
		else
		{
			timerIter->second.timerNextExpiration = currentTime + timerIter->second.timerPeriod;
		}
		return true;
	}
	return false;
}
	
bool CTimerManager::StopTimer(const Int32& timerId)
{
	tTimerInfoIterator timerIter = m_timerInfoMap.find(timerId);
	if (m_timerInfoMap.end() != timerIter )
	{
		timerIter->second.active = false;
		return true;
	}
	return false;
}


void CTimerManager::HandleMessage( CMessage& message )
{
	if ( msgId_Runtime_Timer_1000 == message.GetMessageId() )
	{
		UInt32 currentTime(GetCurrentTime());

		for ( tTimerInfoIterator timerIter = m_timerInfoMap.begin() ; m_timerInfoMap.end() != timerIter ; ++timerIter )
		{
			if ( ( timerIter->second.active ) && ( timerIter->second.timerNextExpiration <= currentTime ) )
			{
				timerIter->second.timerSubscriber->NotifyTimer(timerIter->first);
				timerIter->second.timerNextExpiration = currentTime + timerIter->second.timerPeriod; 
			}
		}
	}
}

const UInt32 CTimerManager::GetCurrentTime()
{
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	
	return ( currentTime.tv_sec*1000 + currentTime.tv_usec/1000 );
}

}
