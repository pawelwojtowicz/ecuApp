#ifndef UCL_CSHARED_STORAGE_H
#define UCL_CSHARED_STORAGE_H
#include <string>

namespace UCL
{

class CSharedStorage
{
public:
	CSharedStorage(const std::string& storageName, const size_t size, const bool owner );
	virtual ~CSharedStorage();

	bool Initialize();
	bool Shutdown();

private:
	std::string m_storageName;

	size_t m_size;

	bool m_owner;

	int m_hSharedMemoryHandle;

	char* m_pMemory;

};

}
#endif
