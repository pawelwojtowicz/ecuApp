#pragma once
#include "CATProtocolAction.h"

namespace ATProtocolEngine
{
class CStopTimeoutAction : public CATProtocolAction
{
/** Used StopTimeout()
		Stops the timeout, "E_TIMEOUT" will not be fired to the state machine of the ATPRotocolEngine */
public:
	CStopTimeoutAction();
	virtual ~CStopTimeoutAction();

	virtual void Execute();

private:
	CStopTimeoutAction(const CStopTimeoutAction&);
	CStopTimeoutAction& operator=(const CStopTimeoutAction&);
};
}
