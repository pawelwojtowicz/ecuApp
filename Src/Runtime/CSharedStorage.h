#ifndef UCL_CSHARED_STORAGE_H
#define UCL_CSHARED_STORAGE_H
#include <UCL/CSharedMemory.h>
#include <UCL/CSemaphore.h>

namespace UCL
{
class CSerializable;
}

namespace Runtime
{

class CSharedStorage
{
public:
	CSharedStorage( );
	virtual ~CSharedStorage();

	bool Initialize(const std::string& storageName, const size_t size, const bool owner);
	bool Shutdown();
		
	bool SetData( UCL::CSerializable& serializableData);
	bool GetData( UCL::CSerializable& serializableData);

private:
	UCL::CSharedMemory m_sharedMemory;
	
	UCL::CSemaphore m_lockFacility;

};

}
#endif
