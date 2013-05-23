#include "CSharedStorage.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>


namespace UCL
{

CSharedStorage::CSharedStorage(const std::string& storageName, const size_t size, const bool owner )
: m_storageName(storageName)
, m_size(size)
, m_owner(owner)
, m_hSharedMemoryHandle(0)
, m_pMemory(0)
{
}


CSharedStorage::~CSharedStorage()
{
}

bool CSharedStorage::Initialize()
{
	bool retVal(false);

	int flags = m_owner?(O_RDWR|O_CREAT):(O_RDONLY);

	m_hSharedMemoryHandle = shm_open( m_storageName.c_str(), flags, S_IRUSR | S_IWUSR );
	if ( m_hSharedMemoryHandle != -1 )
	{
		printf("ok 1\n");
		if (ftruncate(m_hSharedMemoryHandle, m_size) != -1 )
		{
			printf("ok 2\n");

			m_pMemory = (char*)mmap(0, m_size, (m_owner?PROT_WRITE:PROT_READ), MAP_SHARED, m_hSharedMemoryHandle, 0 );

			retVal = ( MAP_FAILED != m_pMemory );

			if (retVal)
			{
				printf("ok 3\n");

			}
		}
	}

	return retVal; 
}

bool CSharedStorage::Shutdown()
{
	bool retVal(false);


	if (-1 != shm_unlink(m_storageName.c_str());
	{
		retVal = true;
	}

	return retVal; 
}




}
