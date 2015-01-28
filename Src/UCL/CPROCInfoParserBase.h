#ifndef UCL_CPROCINFOPARSERBASE_H
#define UCL_CPROCINFOPARSERBASE_H
#include <GlobalTypes.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include "CTokenizer.h"
#define MEMORY_ITEM_SIZE 256

namespace UCL
{

class CPROCInfoParserBase
{

protected:	
	CPROCInfoParserBase(const std::string& infoFileName)
	: m_dataValid(false)
	, m_infoFileName(infoFileName)
	{
	}

	virtual ~CPROCInfoParserBase()
	{
	}
	
public:	
	void Refresh()
	{
		m_dataValid = false;
		this->Reset();
		
		FILE* infoFileDescr = fopen(m_infoFileName.c_str(), "r");
	
		if ( 0 != infoFileDescr)
		{
			size_t infoItemStringSize(MEMORY_ITEM_SIZE);
			char memoryInfoItemString[MEMORY_ITEM_SIZE];
		
			char*  tmp =memoryInfoItemString;
			memset(memoryInfoItemString, 0 , infoItemStringSize);

			while ( getline( &tmp, &infoItemStringSize, infoFileDescr ) >= 0 )
			{
				std::string line(tmp);
				if (this->ParseInfoLine(line))
				{
					m_dataValid = true;
				}
		
				memset(memoryInfoItemString, 0 , infoItemStringSize);			
			}
		
			fclose(infoFileDescr);
		}	
	}

	
	bool IsValid() {return m_dataValid;};	

protected:
	virtual bool ParseInfoLine( const std::string& infoLine) = 0;
	
	virtual void Reset() = 0;
	
private:
	CPROCInfoParserBase(const CPROCInfoParserBase&);
	CPROCInfoParserBase& operator=(const CPROCInfoParserBase&);
	
	bool m_dataValid;
	
	std::string m_infoFileName;
};
}
#endif
