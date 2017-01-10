#pragma once
#include "CATProtocolAction.h"

namespace ATProtocolEngine
{
class COpenPortAction : public CATProtocolAction
{
/** Opens the port configured for the instance of ATProtocolEngine */

public:
	COpenPortAction(IActionExecutionContext& actionExecutionContext);
	virtual ~COpenPortAction();

	virtual void Execute();

private:
	COpenPortAction(const COpenPortAction&);
	COpenPortAction& operator=(const COpenPortAction&);
};
}
