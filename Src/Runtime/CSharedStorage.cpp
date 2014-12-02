#include "CSharedStorage.h"
#include <UCL/CSerializable.h>


namespace Runtime
{

CSharedStorage::CSharedStorage()
: m_sharedMemory()
, m_lockFacility()
{
}


CSharedStorage::~CSharedStorage()
{
}

bool CSharedStorage::Initialize(const std::string& storageName, const size_t size, const bool owner)
{
	bool retVal(false);
	
	retVal = m_sharedMemory.Open(storageName, size, owner);
	
	if (retVal)
	{
		retVal = m_lockFacility.Initialize(storageName, 1);
	}

	return retVal; 
}

bool CSharedStorage::Shutdown()
{
	bool retVal(false);
	
	m_sharedMemory.Close();

	m_lockFacility.Shutdown();

	return retVal; 
}

bool CSharedStorage::SetData( UCL::CSerializable& serializableData)
{
	bool retVal(false);
	m_lockFacility.Lock();
	if (m_sharedMemory.IsValid() )
	{
		retVal = serializableData.Serialize(m_sharedMemory.GetMemoryPointer(),m_sharedMemory.GetMemorySize());
	}
	m_lockFacility.Unlock();	
	return retVal;
}

bool  CSharedStorage::GetData( UCL::CSerializable& serializableData)
{
	bool retVal(false);
	m_lockFacility.Lock();

	if (m_sharedMemory.IsValid() )
	{
		retVal = serializableData.Deserialize(m_sharedMemory.GetMemoryPointer(),m_sharedMemory.GetMemorySize());
	}
	
	m_lockFacility.Unlock();	
	return retVal;
}


}
