#pragma once
#include "CATProtocolAction.h"

namespace ATProtocolEngine
{
class CStartAction : public CATProtocolAction
{
/** Starts a thread, that reads from the serial port */

public:
	CStartAction(IActionExecutionContext& actionExecutionContext);
	virtual ~CStartAction();

	virtual void Execute();

private:
	CStartAction(const CStartAction&);
	CStartAction& operator=(const CStartAction&);
};
}
