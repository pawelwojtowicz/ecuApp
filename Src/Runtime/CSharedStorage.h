#ifndef UCL_CSHARED_STORAGE_H
#define UCL_CSHARED_STORAGE_H
#include <string>
#include <semaphore.h>

namespace Runtime
{

class CSharedStorage
{
public:
	CSharedStorage(const std::string& storageName, const size_t size, const bool owner );
	virtual ~CSharedStorage();

	bool Initialize();
	bool Shutdown();
	
	void LockStorage();	
	void UnlockStorage();

private:
	std::string m_storageName;

	size_t m_size;

	bool m_owner;

	int m_hSharedMemoryHandle;

	char* m_pMemory;
	
	sem_t* m_lockHandle;

};

}
#endif
