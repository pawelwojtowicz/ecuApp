#pragma once
#include "CATProtocolAction.h"

namespace ATProtocolEngine
{
class CClosePortAction : public CATProtocolAction
{
/** Closes the port configured for the ATProtocolEngine instance */

public:
	CClosePortAction(IActionExecutionContext& actionExecutionContext);
	virtual ~CClosePortAction();

	virtual void Execute();

private:
	CClosePortAction(const CClosePortAction&);
	CClosePortAction& operator=(const CClosePortAction&);
};
}
