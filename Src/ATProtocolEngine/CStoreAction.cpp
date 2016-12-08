#include "CStoreAction.h"
#include <UCL/CTokenizer.h>

namespace ATProtocolEngine
{

	CStoreAction::CStoreAction(IActionExecutionContext& actionExecutionContext)
	: CATProtocolAction(actionExecutionContext)
	{
	}
	CStoreAction::~CStoreAction()
	{
	}

	bool CStoreAction::Configure(const CSM::IActionFactory& , const std::string& configurationString)
	{
		UCL::CTokenizer params( configurationString, ",");
		if ( 2 == params.GetTokenCount() )
		{
			m_inputParam = params.GetToken(0);
			m_outputParam = params.GetToken(1);
			return true;
		}
		return false;
	}

	void CStoreAction::Execute()
	{
		if ( GetExecutionContext().GetParameterBundle().IsAvailable(m_inputParam) )
		{
			GetExecutionContext().GetParameterBundle().Store(m_outputParam, GetExecutionContext().GetParameterBundle().GetParameter(m_inputParam));
		}
	}

}
