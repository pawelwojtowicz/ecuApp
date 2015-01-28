#ifndef UCL_CMEMORYINFO_H
#define UCL_CMEMORYINFO_H
#include <GlobalTypes.h>
#include "InfoItemTypes.h"
#include "CPROCInfoParserBase.h"

namespace UCL
{
class CMemoryInfo : public CPROCInfoParserBase
{
	typedef std::map<tMemStatItem,Int32> tMemStatInfo;
	typedef tMemStatInfo::const_iterator tMemStatInfoIter;
public:	
	CMemoryInfo();
	virtual ~CMemoryInfo();
	
	Int32 GetMemoryInfo(const tMemStatItem& memInfoId);
	
protected:
	virtual bool ParseInfoLine( const std::string& infoLine);
	
	virtual void Reset();

private:
	CMemoryInfo(const CMemoryInfo&);
	CMemoryInfo& operator=(const CMemoryInfo&);
	
	tMemStatInfo m_memInfo;
};
}
#endif
