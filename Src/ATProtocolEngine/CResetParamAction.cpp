#include "CResetParamAction.h"
#include <UCL/CTokenizer.h>

namespace ATProtocolEngine
{

	CResetParamAction::CResetParamAction(IActionExecutionContext& actionExecutionContext)
	: CATProtocolAction(actionExecutionContext)
	, m_paramName()
	{
	}
	CResetParamAction::~CResetParamAction()
	{
	}

	bool CResetParamAction::Configure(const CSM::IActionFactory& , const std::string& configurationString)
	{
		if ( !configurationString.empty())
		{
			m_paramName = configurationString;
			return true;
		}
		return false;
	}

	void CResetParamAction::Execute()
	{
		if ( GetExecutionContext().GetParameterBundle().IsAvailable(m_paramName) )
		{
			GetExecutionContext().GetParameterBundle().Reset( m_paramName );
		}
	}

}
