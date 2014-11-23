#include "CPublicProcessInfo.h"

namespace Controller
{

CPublicProcessInfo::CPublicProcessInfo()
{
}

CPublicProcessInfo::~CPublicProcessInfo()
{
}

bool CPublicProcessInfo::ToByteStream()
{
	UInt32 itemCount(m_processInfos.size());

	bool retVal( SetValue(itemCount));
	for ( UInt32 itemNo= 0 ; ( itemNo < itemCount ) && retVal ; ++itemCount )
	{
		retVal &=	SetValue(m_processInfos[itemNo].ProcessID);
		retVal &=	SetValue(m_processInfos[itemNo].ProcessName);
		retVal &=	SetValue(m_processInfos[itemNo].VersionInformation);
		retVal &=	SetValue(static_cast<UInt8>(m_processInfos[itemNo].UnitState));
	}
	return retVal;
}

bool CPublicProcessInfo::FromByteStream()
{
	UInt32 itemCount(0);

	bool retVal( GetValue(itemCount));
	for ( UInt32 itemNo= 0 ; ( itemNo < itemCount ) && retVal ; ++itemCount )
	{
		ProcessInfoStruct infoStruct;
		retVal &=	GetValue(infoStruct.ProcessID);
		retVal &=	GetValue(infoStruct.ProcessName);
		retVal &=	GetValue(infoStruct.VersionInformation);
		UInt8 unitStateInInt(0);
		retVal &=	GetValue(unitStateInInt);
		
		infoStruct.UnitState = static_cast<tProcessStatus>(unitStateInInt);
		
		m_processInfos.push_back(infoStruct);
	}
	return retVal;
}

size_t CPublicProcessInfo::GetStorageSize()
{
	size_t requiredStorage(0);
		
	//strcture size
	requiredStorage += sizeof(UInt32);				// ProcessID
	requiredStorage += GetStringSpace( 20 ); 	// Process name - assume 20 characters
	requiredStorage += GetStringSpace( 20 ); 	// VersionInformation - assume 20 characters
	requiredStorage += sizeof(UInt8);					// tProcessStatus is casted to UInt8
	requiredStorage *= PROCESS_COUNT ; 				//multiply with the assumed elementCount 
	
	requiredStorage += sizeof(UInt32); 				// element Count

	return requiredStorage;
}


}
