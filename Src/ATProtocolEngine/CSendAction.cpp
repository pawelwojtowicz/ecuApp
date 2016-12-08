#include "CSendAction.h"

namespace ATProtocolEngine
{
CSendAction::CSendAction(IActionExecutionContext& actionExecutionContext)
: CATProtocolAction(actionExecutionContext)
, m_messageTag()
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

	GetExecutionContext().GetSerialPortHandler().SendCommand(message);
}
}
