#ifndef UCL_CMEMORYINFO_H
#define UCL_CMEMORYINFO_H
#include <GlobalTypes.h>

namespace UCL
{
class CMemoryInfo
{
public:
	typedef enum
	{
		MemTotal,
		MemFree,
		Buffers,Cached,
		SwapCached,
		Active,
		Inactive,
		Shmem,
		NotAnItem
	} tMemStatItem;
	
	CMemoryInfo();
	virtual ~CMemoryInfo();
	
	void RefreshMemoryInformation();
	
	Int32 GetMemInfoItem( const tMemStatItem& itemId );
	
	bool IsValid() {return m_dataValid;};
private:
	CMemoryInfo(const CMemoryInfo&);
	CMemoryInfo& operator=(const CMemoryInfo&);
private:
	typedef std::map<tMemStatItem, Int32> tMemStatItems;
	typedef tMemStatItems::const_iterator tMemStatItemConstIter;
	
	bool m_dataValid;

	tMemStatItems m_statItems;
};
}
#endif
