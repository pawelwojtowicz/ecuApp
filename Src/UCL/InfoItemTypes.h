#ifndef UCL_INFOITEMTYPES_H
#define UCL_INFOITEMTYPES_H

namespace UCL
{
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
}

#endif
