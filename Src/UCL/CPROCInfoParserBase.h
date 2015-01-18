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

template <typename ITEM_ENUMERATION, typename ITEM_VALUE>
class CPROCInfoParserBase
{
	typedef typename std::map<ITEM_ENUMERATION, ITEM_VALUE> tInfoItems;
	typedef typename tInfoItems::const_iterator tInfoItemsConstIter;

protected:	
	CPROCInfoParserBase(const std::string& infoFileName, UInt8 requiredFields)
	: m_dataValid(false)
	, m_requiredFields(requiredFields)
	, m_infoFileName(infoFileName)
	{
		Refresh();
	}

	virtual ~CPROCInfoParserBase()
	{
	}
	
public:	
	void Refresh()
	{
		m_dataValid = false;
		m_infoItems.clear();
		FILE* infoFileDescr = fopen(m_infoFileName.c_str(), "r");
	
		if ( 0 != infoFileDescr)
		{
			UInt8 fieldCount(0);
			size_t infoItemStringSize(MEMORY_ITEM_SIZE);
			char memoryInfoItemString[MEMORY_ITEM_SIZE];
		
			char*  tmp =memoryInfoItemString;
			memset(memoryInfoItemString, 0 , infoItemStringSize);

			while ( getline( &tmp, &infoItemStringSize, infoFileDescr ) >= 0 )
			{
				if (ParseInfoLine(tmp))
				{
					++fieldCount;
				}
		
				memset(memoryInfoItemString, 0 , infoItemStringSize);			
			}
		
			fclose(infoFileDescr);
		
			if ( fieldCount >= m_requiredFields )
			{
				m_dataValid = true;
			}
		}	
	}

	
	bool GetMemInfoItem( const ITEM_ENUMERATION& itemId, ITEM_VALUE& value )
	{
		tInfoItemsConstIter pCIter = m_infoItems.find(itemId);
	
		if (m_infoItems.end() != pCIter)
		{
			value = pCIter->second;
			return true;
		}
	
		return false;
	}
	
	bool IsValid() {return m_dataValid;};	
private:
	virtual bool ParseInfoLine( const std::string& infoLine) = 0;
	
protected:
	void AddInfoItem(const ITEM_ENUMERATION& infoItemId, const ITEM_VALUE& value )
	{
		m_infoItems.insert(typename tInfoItems::value_type(infoItemId,value));
	}
		
private:
	CPROCInfoParserBase(const CPROCInfoParserBase&);
	CPROCInfoParserBase& operator=(const CPROCInfoParserBase&);
	
	bool m_dataValid;
	
	UInt8 m_requiredFields;

	tInfoItems m_infoItems;
	
	std::string m_infoFileName;
};
}
#endif
