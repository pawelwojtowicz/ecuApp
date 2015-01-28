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
: CPROCInfoParserBase(std::string("/proc/meminfo"))
{
	Refresh();
}

CMemoryInfo::~CMemoryInfo()
{
}

bool CMemoryInfo::ParseInfoLine( const std::string& infoLine)
{
	CTokenizer memoryItemExtractor( infoLine,":" );
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
			itemId = Active;
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
				m_memInfo.insert(tMemStatInfo::value_type(itemId,value));
				
				if ( 8 == m_memInfo.size() )
				{
					return true;
				}
			}
		}
	}
	return false;
}

void CMemoryInfo::Reset()
{
	m_memInfo.clear();
}

Int32 CMemoryInfo::GetMemoryInfo(const tMemStatItem& memInfoId)
{
	tMemStatInfoIter pCIter = m_memInfo.find(memInfoId);
	if ( m_memInfo.end() != pCIter)
	{
		return pCIter->second;
	}

	return -1;
}


}

