#include "CSharedMemory.h"
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/stat.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>

namespace UCL
{

CSharedMemory::CSharedMemory()
: m_storageName()
, m_size(0)
, m_owner(false)
, m_hSharedMemoryHandle(-1)
, m_pMemory(0)
{
}

CSharedMemory::~CSharedMemory()
{
}

bool CSharedMemory::Open(const std::string& sharedRegionName, size_t sharedRegionSize, bool owner )
{
	bool retVal(false);
	
	// shared storage name
	m_storageName = sharedRegionName;
	
	// are we the owner?
	m_owner = owner;
	
	// set up the size of the shared memory
	m_size = sharedRegionSize;
	
	//read/right rights?
	int flags = m_owner? (O_CREAT| O_RDWR ):(O_RDONLY);
	
	// file access rights
	mode_t fileAccessRights(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP| S_IROTH | S_IWOTH);
	
	// create shared memory object
	m_hSharedMemoryHandle = shm_open( m_storageName.c_str(), flags, fileAccessRights );
	
	if ( -1 != m_hSharedMemoryHandle )
	{
		if ( m_owner )
		{
			// adjust the size of the memory
			if (-1 != ftruncate(m_hSharedMemoryHandle, m_size) )
			{
				m_pMemory = (Int8*)mmap(0, m_size, (PROT_WRITE | PROT_READ) , MAP_SHARED, m_hSharedMemoryHandle, 0 );
			}
		}
		else
		{
			m_pMemory = (Int8*)mmap(0, m_size, PROT_READ, MAP_SHARED, m_hSharedMemoryHandle, 0 );
		}
		retVal = ( MAP_FAILED != m_pMemory );
	}
	
	if (!retVal)
	{
		m_pMemory = 0;
	}
	
	return retVal;
}

void CSharedMemory::Close()
{
	munmap(m_pMemory,m_size); 

	shm_unlink(m_storageName.c_str());
}

bool CSharedMemory::IsValid()
{
	return ( 0 != m_pMemory );
}

Int8* CSharedMemory::GetMemoryPointer()
{
	return m_pMemory;
}

UInt32 CSharedMemory::GetMemorySize()
{
	return m_size;
}

}
