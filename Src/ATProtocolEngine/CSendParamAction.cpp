#include "CSendParamAction.h"
#include <Logger/Logger.h>

static std::string sString_characterCR("\r");

namespace ATProtocolEngine
{
CSendParamAction::CSendParamAction(IActionExecutionContext& actionExecutionContext, bool sendLine )
: CATProtocolAction(actionExecutionContext)
, m_variableName()
, m_sendLine(sendLine)
{
}

CSendParamAction::~CSendParamAction()
{
}

bool CSendParamAction::Configure( const CSM::IActionFactory& ,const std::string& config )
{
	m_variableName = config;
	return true;
}

void CSendParamAction::Execute()
{
	std::string message(GetExecutionContext().GetParameterBundle().GetParameter(m_variableName));


	RETAILMSG(DATA, ("CSendParamAction::Execute() - %s", message.c_str()));
	if ( m_sendLine )
	{
		message += sString_characterCR;
	}

	GetExecutionContext().GetSerialPortHandler().SendCommand(message);
}
}
