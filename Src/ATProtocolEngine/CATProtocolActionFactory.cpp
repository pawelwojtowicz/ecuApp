#include "CATProtocolActionFactory.h"
#include <CSM/IAction.h>
#include <CSM/ICondition.h>
#include "CATProtocolAction.h"
#include <UCL/CTokenizer.h>
#include "IActionExecutionContext.h"
#include "IATProtocolActionFactory.h"

#include "CSendAction.h"
#include "CCompositeAction.h"
#include "CStartTimeoutAction.h"
#include "CStopTimeoutAction.h"
#include "CStoreAction.h"
#include "COpenPortAction.h"
#include "CClosePortAction.h"
#include "CStartAction.h"
#include "CStopAction.h"

namespace ATProtocolEngine
{

CATProtocolActionFactory::CATProtocolActionFactory(IActionExecutionContext& rExecutionContext)
: m_rActionExecutionContext(rExecutionContext)
, m_pAuxiliaryActionFactory(0)
{
}

CATProtocolActionFactory::~CATProtocolActionFactory()
{
}

void CATProtocolActionFactory::RegisterActionFactory( IATProtocolActionFactory& rATProtocolActionFactory )
{
	m_pAuxiliaryActionFactory = &rATProtocolActionFactory;
}

CSM::IAction* CATProtocolActionFactory::GetAction( const std::string& actionName ) const
{
	CATProtocolAction* pAction(0);

	std::string actionId(actionName);
	std::string actionParameters;

	UCL::CTokenizer actionGroup(actionName, ";");
	UInt32 tokenCount( actionGroup.GetTokenCount() );
	if (1 < tokenCount)
	{
		actionId = std::string("composite"); 
		actionParameters = actionName;
	}
	else
	{
		UCL::CTokenizer actionNameParser(actionName,"(");
		if ( 2 == actionNameParser.GetTokenCount() )
		{
			actionId = actionNameParser.GetToken(0);
			actionParameters = actionNameParser.GetToken(1);

			if ( ')' == actionParameters.back() )
			{
				actionParameters.pop_back();
			}		
		}
	}

	pAction = CreateActionInstance( actionId );

	if ( 0!= pAction )
	{
		if (!pAction->Configure(*this, actionParameters))
		{
			delete pAction;
			pAction = 0;
		}
	}

	return pAction;
}
	
CSM::ICondition* CATProtocolActionFactory::GetCondition( const std::string& conditionName) const
{
	return 0;
}

CATProtocolAction* CATProtocolActionFactory::CreateActionInstance( const std::string& actionName ) const
{
	CATProtocolAction* pActionInstance(0);

	if ( !actionName.compare("send") )
	{
		pActionInstance = new CSendAction(m_rActionExecutionContext, false);
	}
	else if ( !actionName.compare("sendLine") )
	{
		pActionInstance = new CSendAction(m_rActionExecutionContext, true);
	}
	else if ( !actionName.compare("startTimer") )
	{
		pActionInstance = new CStartTimeoutAction(m_rActionExecutionContext);
	}
	else if ( !actionName.compare("stopTimer") )
	{
		pActionInstance = new CStopTimeoutAction(m_rActionExecutionContext);
	}
	else if ( !actionName.compare("store") )
	{
		pActionInstance = new CStoreAction(m_rActionExecutionContext);
	}
	else if ( !actionName.compare("composite") )
	{
		pActionInstance = new CCompositeAction(m_rActionExecutionContext);
	}
	else if ( !actionName.compare("openPort") )
	{
		pActionInstance = new COpenPortAction(m_rActionExecutionContext);
	}
	else if ( !actionName.compare("closePort") )
	{
		pActionInstance = new CClosePortAction(m_rActionExecutionContext);
	}
	else if ( !actionName.compare("start") )
	{
		pActionInstance = new CStartAction(m_rActionExecutionContext);
	}
	else if ( !actionName.compare("stop") )
	{
		pActionInstance = new CStopAction(m_rActionExecutionContext);
	}
	else
	{
		if ( 0 != m_pAuxiliaryActionFactory )
		{
			pActionInstance = m_pAuxiliaryActionFactory->CreateActionInstance(actionName);
		}
	}


	return pActionInstance;
}


}
