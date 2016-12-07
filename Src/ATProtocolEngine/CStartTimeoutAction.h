#pragma once
#include "CATProtocolAction.h"

namespace ATProtocolEngine
{
class CStartTimeoutAction : public CATProtocolAction
{
/** Used StartTimeout(timeoutValue[s])
		Start the timeout, after which "E_TIMEOUT" event fill be fired to the state machine of the ATPRotocolEngine */
public:
	CStartTimeoutAction();
	virtual ~CStartTimeoutAction();

	virtual void Execute();

private:
	CStartTimeoutAction(const CStartTimeoutAction&);
	CStartTimeoutAction& operator=(const CStartTimeoutAction&);
};
}
