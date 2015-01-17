#include "CMemoryInfo.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include "CTokenizer.h"
#define MEMORY_ITEM_SIZE 256

namespace UCL
{
CMemoryInfo::CMemoryInfo()
: m_dataValid(false)
{

}

CMemoryInfo::~CMemoryInfo()
{
}
	
void CMemoryInfo::RefreshMemoryInformation()
{
	m_dataValid = false;
	UInt8 neededItems = 5;
	m_statItems.clear();
	FILE* memoryInfoFilePointer = fopen("/proc/meminfo", "r");
	
	if ( 0 != memoryInfoFilePointer)
	{
		size_t memoryItemSize(MEMORY_ITEM_SIZE);
		char memoryInfoItemString[MEMORY_ITEM_SIZE];
		
		char*  tmp =memoryInfoItemString;
		memset(memoryInfoItemString, 0 , MEMORY_ITEM_SIZE);

		while ( getline( &tmp, &memoryItemSize, memoryInfoFilePointer ) >= 0 )
		{
			CTokenizer memoryItemExtractor( memoryInfoItemString,MEMORY_ITEM_SIZE,":" );
			if ( 2 == memoryItemExtractor.GetTokenCount() )
			{
				if (memoryItemExtractor.GetToken(0) == std::string("MemTotal"))
				{
					printf("znalazlem %s\n", memoryItemExtractor.GetToken(0).c_str());
				}
			}
		
			memset(memoryInfoItemString, 0 , MEMORY_ITEM_SIZE);			
		}
	}
	
	m_dataValid = ( 0 == neededItems ); 
}
	
Int32 CMemoryInfo::GetMemInfoItem( const tMemStatItem& itemId )
{
	tMemStatItemConstIter pCIter = m_statItems.find(itemId);
	
	if (m_statItems.end() != pCIter)
	{
		return pCIter->second;
	}
	
	return -1;
}
}

