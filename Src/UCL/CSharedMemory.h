#ifndef UCL_CSHAREDMEMORY_H
#define UCL_CSHAREDMEMORY_H
#include <GlobalTypes.h>

namespace UCL
{

class CSharedMemory
{
public:
	CSharedMemory();
	virtual ~CSharedMemory();
	
	bool Open(const std::string& sharedRegionName, size_t sharedRegionSize, bool owner );
	void Close();
	
	bool IsValid();
	
	Int8* GetMemoryPointer();
	UInt32 GetMemorySize();

private:
	std::string m_storageName;

	size_t m_size;

	bool m_owner;

	int m_hSharedMemoryHandle;

	Int8* m_pMemory;
};

}
#endif
