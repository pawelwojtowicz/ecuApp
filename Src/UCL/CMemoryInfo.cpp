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
	UInt8 neededItems = 7;
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
				tMemStatItem itemId(NotAnItem);
				
				if (memoryItemExtractor.GetToken(0) == std::string("MemTotal"))
				{
					itemId = MemTotal;
				}
				else if (memoryItemExtractor.GetToken(0) == std::string("MemFree"))
				{
					itemId = MemFree;
				}
				else if (memoryItemExtractor.GetToken(0) == std::string("Buffers"))
				{
					itemId = Buffers;
				}
				else if (memoryItemExtractor.GetToken(0) == std::string("Cached"))
				{
					itemId = Cached;
				}
				else if (memoryItemExtractor.GetToken(0) == std::string("SwapCached"))
				{
					itemId = SwapCached;
				}
				else if (memoryItemExtractor.GetToken(0) == std::string("Active"))
				{
					itemId = SwapCached;
				}
				else if (memoryItemExtractor.GetToken(0) == std::string("Inactive"))
				{
					itemId = Inactive;
				}
				else if (memoryItemExtractor.GetToken(0) == std::string("Shmem"))
				{
					itemId = Shmem;
				}
				
				if (NotAnItem != itemId)
				{
					Int32 value(-1);
					
					std::string valueString(memoryItemExtractor.GetToken(1));				
					valueString.erase(valueString.find("kB"));
					
					value = atoi(valueString.c_str());
					
					if (-1 != value)
					{
						m_statItems.insert(tMemStatItems::value_type(itemId, value));
						--neededItems;
					}
				}

			}
		
			memset(memoryInfoItemString, 0 , memoryItemSize);			
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

