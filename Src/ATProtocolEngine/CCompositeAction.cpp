#include "CCompositeAction.h"
#include <UCL/CTokenizer.h>
#include <algorithm>

namespace ATProtocolEngine
{
CCompositeAction::CCompositeAction(IActionExecutionContext& executionContext)
: CATProtocolAction(executionContext)
{
}

CCompositeAction::~CCompositeAction()
{
	for (tATProtocolActions::iterator iter = m_actions.begin() ; m_actions.end() != iter ; ++iter)
	{
		delete *iter;
	}
}

bool CCompositeAction::Configure( const CSM::IActionFactory& rFactory, const std::string& configurationString )
{
	bool retVal(false);
	UCL::CTokenizer commands(configurationString, ";");
	UInt32 commandCount(commands.GetTokenCount());
	for (UInt32 i = 0 ; i < commandCount ; ++i)
	{
		CSM::IAction* pAction(rFactory.GetAction(commands.GetToken(i)));
		if ( 0 != pAction )
		{
			m_actions.push_back(pAction);
			retVal = true;
		}
	}
	
	return retVal;
}

void CCompositeAction::Execute()
{
	std::for_each(m_actions.begin(), m_actions.end(), std::mem_fun(&CSM::IAction::Execute));
}


}
