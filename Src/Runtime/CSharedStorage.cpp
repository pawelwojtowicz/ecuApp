#include "CSharedStorage.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


namespace Runtime
{

CSharedStorage::CSharedStorage(const std::string& storageName, const size_t size, const bool owner )
: m_storageName(storageName)
, m_size(size)
, m_owner(owner)
, m_hSharedMemoryHandle(-1)
, m_pMemory(0)
, m_lockHandle(SEM_FAILED)
{
}


CSharedStorage::~CSharedStorage()
{
}

bool CSharedStorage::Initialize()
{
	bool retVal(false);

	int flags = m_owner?(O_RDWR|O_CREAT):(O_RDONLY|O_CREAT);

	m_hSharedMemoryHandle = shm_open( m_storageName.c_str(), flags, S_IRUSR | S_IWUSR );
	if ( m_hSharedMemoryHandle != -1 )
	{
		if (ftruncate(m_hSharedMemoryHandle, m_size) != -1 )
		{
			m_pMemory = (char*)mmap(0, m_size, (m_owner?PROT_WRITE:PROT_READ), MAP_SHARED, m_hSharedMemoryHandle, 0 );

			retVal = ( MAP_FAILED != m_pMemory );

			if (retVal)
			{
				std::string semaphoreName(m_storageName+std::string("Lock"));
				m_lockHandle = sem_open(semaphoreName.c_str(), O_CREAT , ( S_IRWXO | S_IRWXG | S_IRWXU) , 1 );
				if (SEM_FAILED != m_lockHandle )
				{
					retVal = true;
				}
				else
				{
					printf("Failed sem_open [%s]\n", strerror(errno));
				}
			}
		}
	}

	return retVal; 
}

bool CSharedStorage::Shutdown()
{
	bool retVal(false);


	if (-1 != shm_unlink( m_storageName.c_str() ) )
	{
		retVal = true;
	}
	
	sem_close(m_lockHandle);

	return retVal; 
}

void CSharedStorage::LockStorage()
{
	sem_wait(m_lockHandle);
}

void CSharedStorage::UnlockStorage()
{
	sem_post(m_lockHandle);
}



}
