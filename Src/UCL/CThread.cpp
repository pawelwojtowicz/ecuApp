#include "CThread.h"
#include <signal.h>

namespace UCL
{
CThread::CThread( const std::string& threadName )
: m_threadName(threadName)
, m_cancellationState(PTHREAD_CANCEL_DISABLE)
, m_cancellationType(PTHREAD_CANCEL_ASYNCHRONOUS)
{
}

CThread::~CThread()
{
}

void CThread::Start()
{
	pthread_create(&m_threadHandle,0,CThread::ThreadRunner,(void *)this);
}


void CThread::Terminate()
{
	if ( 0 == pthread_cancel(m_threadHandle) )
	{
		if ( WaitFor() )
		{
			CleanUp();
		}
	}
}

void* CThread::ThreadRunner( void* pThreadInstance )
{
	CThread* pThread = (CThread*)pThreadInstance;
	if ( 0 != pThread )
	{
		pthread_setcancelstate(pThread->m_cancellationState,0);
		pthread_setcanceltype(pThread->m_cancellationType,0);
		pThread->Run();
	}
	pthread_exit(0);
}

bool CThread::WaitFor()
{
	return ( 0 == pthread_join(m_threadHandle,0) );
}

void CThread::AllowTermination(const bool allowFlag)
{
	if ( allowFlag )
	{
		m_cancellationState = PTHREAD_CANCEL_DISABLE ;
	}
	else
	{
		m_cancellationState = PTHREAD_CANCEL_ENABLE ;
	}

	if ( 0 == pthread_kill(m_threadHandle, 0) )
	{
		pthread_setcancelstate(m_cancellationState,0);
	}
}


}
