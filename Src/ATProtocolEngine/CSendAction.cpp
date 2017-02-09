#include "CSendAction.h"
#include <Logger/Logger.h>

static std::string sString_characterCR("\r");

namespace ATProtocolEngine
{
CSendAction::CSendAction(IActionExecutionContext& actionExecutionContext, bool sendLine )
: CATProtocolAction(actionExecutionContext)
, m_messageTag()
, m_sendLine(sendLine)
{
}

CSendAction::~CSendAction()
{
}

bool CSendAction::Configure( const CSM::IActionFactory& ,const std::string& config )
{
	m_messageTag = config;
	return true;
}

void CSendAction::Execute()
{
	std::string message;

	if ( !GetExecutionContext().GetSerializationEngine().SerializeMsg( m_messageTag, GetExecutionContext().GetParameterBundle(), message ) )
	{
		message = m_messageTag;
	}

	RETAILMSG(DATA, ("CSendAction::Execute() - %s", message.c_str()));
	printf("sendLine(%s)\n", message.c_str());
	if ( m_sendLine )
	{
		message += sString_characterCR;
	}

	GetExecutionContext().GetSerialPortHandler().SendCommand(message);
}
}
