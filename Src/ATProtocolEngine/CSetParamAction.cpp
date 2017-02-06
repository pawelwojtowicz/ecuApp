#include "CSetParamAction.h"
#include <UCL/CTokenizer.h>

namespace ATProtocolEngine
{

	CSetParamAction::CSetParamAction(IActionExecutionContext& actionExecutionContext)
	: CATProtocolAction(actionExecutionContext)
	, m_paramName()
	, m_paramValue()
	{
	}
	CSetParamAction::~CSetParamAction()
	{
	}

	bool CSetParamAction::Configure(const CSM::IActionFactory& , const std::string& configurationString)
	{
		UCL::CTokenizer params( configurationString, ",");
		if ( 2 == params.GetTokenCount() )
		{
			m_paramName = params.GetToken(0);
			m_paramValue = params.GetToken(1);
			return true;
		}
		return false;
	}

	void CSetParamAction::Execute()
	{
		GetExecutionContext().GetParameterBundle().Store( m_paramName, m_paramValue );
	}

}
