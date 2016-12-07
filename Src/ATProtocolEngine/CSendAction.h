#pragma once
#include "CATProtocolAction.h"

namespace ATProtocolEngine
{
class CSendAction : public CATProtocolAction
{
/** Used Send(msgId)
		serializes the msg, using the IserializationEngine+CParameterBundle, and writes serialized data into the ISerialPortHandler */

	std::list<CATProtocolAction*> tATProtocolActions;
public:
	CSendAction();
	virtual ~CSendAction();

	virtual void Execute();

private:
	CSendAction(const CSendAction&);
	CSendAction& operator=(const CSendAction&);

	tATProtocolActions m_actions;
};
}

