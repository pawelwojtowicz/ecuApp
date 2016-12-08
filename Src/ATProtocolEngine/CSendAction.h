#pragma once
#include "CATProtocolAction.h"

namespace ATProtocolEngine
{
class CSendAction : public CATProtocolAction
{
/** Used Send(msgId)
		serializes the msg, using the IserializationEngine+CParameterBundle, and writes serialized data into the ISerialPortHandler */

public:
	CSendAction(IActionExecutionContext& actionExecutionContext);
	virtual ~CSendAction();

	virtual bool Configure( const CSM::IActionFactory& , const std::string& configurationString );

	virtual void Execute();

private:
	CSendAction(const CSendAction&);
	CSendAction& operator=(const CSendAction&);

	std::string m_messageTag;
};
}
