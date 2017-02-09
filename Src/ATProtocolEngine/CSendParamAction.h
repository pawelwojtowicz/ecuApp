#pragma once
#include "CATProtocolAction.h"

namespace ATProtocolEngine
{
class CSendParamAction : public CATProtocolAction
{
/** Used Send(msgId)
		serializes the msg, using the IserializationEngine+CParameterBundle, and writes serialized data into the ISerialPortHandler */

public:
	CSendParamAction(IActionExecutionContext& actionExecutionContext, bool sendLine);
	virtual ~CSendParamAction();

	virtual bool Configure( const CSM::IActionFactory& , const std::string& configurationString );

	virtual void Execute();

private:
	CSendParamAction(const CSendParamAction&);
	CSendParamAction& operator=(const CSendParamAction&);

	std::string m_variableName;
	
	bool m_sendLine;
	
};
}
