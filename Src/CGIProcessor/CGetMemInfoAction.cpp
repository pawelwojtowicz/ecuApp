#include "CGetMemInfoAction.h"
#include <UCL/CMemoryInfo.h>
#include <JSONLib/json.h>

namespace CGIProcessor
{

CGetMemInfoAction::CGetMemInfoAction(CProxyProvider&)
{
}

CGetMemInfoAction::~CGetMemInfoAction()
{
}

bool CGetMemInfoAction::Execute(const CEnvironment& variables, json::Object& commandOutput)
{
	UCL::CMemoryInfo memInfo;
	
	if ( memInfo.IsValid() )
	{
		json::Object meminfoItem;
		Int32 memoryAmount(0);
		if ( memInfo.GetInfoItem(UCL::MemTotal,memoryAmount))
		{
			meminfoItem["MemTotal"] = memoryAmount; 
		}
		
		if ( memInfo.GetInfoItem(UCL::MemFree,memoryAmount))
		{
			meminfoItem["MemFree"] = memoryAmount; 
		}

		if ( memInfo.GetInfoItem(UCL::Buffers,memoryAmount))
		{
			meminfoItem["Buffers"] = memoryAmount;
		}
		
		if ( memInfo.GetInfoItem(UCL::Cached,memoryAmount))
		{
			meminfoItem["Cached"] = memoryAmount; 
		}

		if ( memInfo.GetInfoItem(UCL::SwapCached,memoryAmount))
		{
			meminfoItem["SwapCached"] = memoryAmount; 
		}

		if ( memInfo.GetInfoItem(UCL::Active,memoryAmount))
		{
			meminfoItem["Active"] = memoryAmount; 
		}

		if ( memInfo.GetInfoItem(UCL::Inactive,memoryAmount))
		{
			meminfoItem["Inactive"] = memoryAmount; 
		}

		if ( memInfo.GetInfoItem(UCL::SwapCached,memoryAmount))
		{
			meminfoItem["Shmem"] = memoryAmount; 
		}
	
		commandOutput["meminfo"] = meminfoItem;
		return true;
	}
	return false;
}

}
