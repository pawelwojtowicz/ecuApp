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
		meminfoItem["MemTotal"] 	= memInfo.GetMemoryInfo(UCL::MemTotal); 
		meminfoItem["Buffers"] 		= memInfo.GetMemoryInfo(UCL::Buffers);
		meminfoItem["MemFree"] 		= memInfo.GetMemoryInfo(UCL::MemFree); 
		meminfoItem["Cached"] 		= memInfo.GetMemoryInfo(UCL::Cached);
		meminfoItem["SwapCached"]	= memInfo.GetMemoryInfo(UCL::SwapCached);
		meminfoItem["Active"] 		= memInfo.GetMemoryInfo(UCL::Active);
		meminfoItem["Inactive"] 	= memInfo.GetMemoryInfo(UCL::Inactive);
		meminfoItem["Shmem"] 			= memInfo.GetMemoryInfo(UCL::Shmem);
	
		commandOutput["meminfo"] = meminfoItem;
		return true;
	}
	return false;
}

}
