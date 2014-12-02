#include "CSemaphore.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

namespace UCL
{

CSemaphore::CSemaphore()
: m_lockHandle(SEM_FAILED)
{
}

CSemaphore::~CSemaphore()
{
}
	
bool CSemaphore::Initialize(const std::string& semaphoreName, const UInt32 semaphoreCount)
{
	m_lockHandle = sem_open(semaphoreName.c_str(), O_CREAT , ( S_IRWXO | S_IRWXG | S_IRWXU) , 1 );
	
	return ( SEM_FAILED != m_lockHandle );
}

void CSemaphore::Shutdown ()
{
	sem_close(m_lockHandle);
}

void CSemaphore::Lock()
{
	sem_wait(m_lockHandle);
}

void CSemaphore::Unlock()
{
	sem_post(m_lockHandle);
}

}
