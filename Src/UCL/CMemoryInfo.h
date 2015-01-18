#ifndef UCL_CMEMORYINFO_H
#define UCL_CMEMORYINFO_H
#include <GlobalTypes.h>
#include "InfoItemTypes.h"
#include "CPROCInfoParserBase.h"

namespace UCL
{
class CMemoryInfo : public CPROCInfoParserBase<tMemStatItem,Int32>
{
public:	
	CMemoryInfo();
	virtual ~CMemoryInfo();
	
private:
	virtual bool ParseInfoLine( const std::string& infoLine);

private:
	CMemoryInfo(const CMemoryInfo&);
	CMemoryInfo& operator=(const CMemoryInfo&);	
};
}
#endif
