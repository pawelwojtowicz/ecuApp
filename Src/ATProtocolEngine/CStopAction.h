#pragma once
#include "CATProtocolAction.h"

namespace ATProtocolEngine
{
class CStopAction : public CATProtocolAction
{
/** Stops a thread that reads from the serial port configured for the instance of ATProtocolEngine */
public:
	CStopAction(IActionExecutionContext& actionExecutionContext);
	virtual ~CStopAction();

	virtual void Execute();

private:
	CStopAction(const CStopAction&);
	CStopAction& operator=(const CStopAction&);
};
}
