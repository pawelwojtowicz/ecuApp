#include "CControllerAction.h"
#include "CGIProcessorConst.h"
#include "CEnvironment.h"
#include "CProxyProvider.h"
#include <ControllerInterface/CControllerProxy.h>
#include <stdio.h>

namespace CGIProcessor
{
CControllerAction::CControllerAction(CProxyProvider& rProxyProvider)
: m_pControllerProxy( rProxyProvider.GetControllerProxy() )
{
}

bool CControllerAction::Execute( const CEnvironment& environment )
{
  bool retVal(false);
  if ( 0 != m_pControllerProxy )
  {
    std::string apiName = environment.GetVariable(s_const_sv_apiName);
    if ( apiName=="shutdown" )
    {
      printf("robie shutdown\n");
        retVal = m_pControllerProxy->RequestShutdown();
    }
    else if ( apiName=="restart" )
    {
      printf("robie restart\n");
      retVal = m_pControllerProxy->RequestRestart();
    }
  }
  return retVal;
}
}
