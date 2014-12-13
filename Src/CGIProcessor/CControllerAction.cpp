#include "CControllerAction.h"
#include "CGIProcessorConst.h"
#include "CEnvironment.h"
#include "CProxyProvider.h"
#include <ControllerInterface/CControllerProxy.h>
#include <ControllerInterface/CPublicProcessInfo.h>
#include "JSONLib/json.h"
#include <stdio.h>

namespace CGIProcessor
{
CControllerAction::CControllerAction(CProxyProvider& rProxyProvider)
: m_pControllerProxy( rProxyProvider.GetControllerProxy() )
{
}

bool CControllerAction::Execute( const CEnvironment& environment , json::Object& commandOutput)
{
  bool retVal(false);
  if ( 0 != m_pControllerProxy )
  {
    std::string apiName = environment.GetVariable(s_const_sv_apiName);
    if ( apiName=="shutdown" )
    {
			retVal = m_pControllerProxy->RequestShutdown();
    }
    else if ( apiName=="restart" )
    {
      retVal = m_pControllerProxy->RequestRestart();
    }
    else if ( apiName=="get_process_list")
    {
	    Controller::CPublicProcessInfo processInfo;
	    m_pControllerProxy->GetCurrentProcessInfo(processInfo);
    
	    Controller::CPublicProcessInfo::tPublicProcessInfoList list = processInfo.GetProcessInfo();
	    
			json::Array processListArray;
    
	    for ( Controller::CPublicProcessInfo::tPublicProcessInfoIter 	iter = list.begin() ; 
    																															iter != list.end() ; 
    																															++iter)
    	{
    		json::Object processItem;
#pragma message("tutaj sprawdzic kuna - nie ma UInt32 w moim JSONie?")
    		processItem["processId"] = static_cast<int>(iter->ProcessID);
    		
    		processItem["name"] = iter->ProcessName.c_str();
    		processItem["versionInfo"] = iter->VersionInformation.c_str();
    		processItem["unitState"] = iter->UnitState;
    		processListArray.push_back(processItem);
    	}
    	
    	commandOutput["processList"] = processListArray;
    }
  }
  return retVal;
}
}
