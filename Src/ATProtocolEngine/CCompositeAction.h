#pragma once
#include "CATProtocolAction.h"
#include <list>

namespace ATProtocolEngine
{
class CCompositeAction : public CATProtocolAction
{
/** Used when the action line consist of many actions separated by ;
		Actions will be executed one after another. */

	typedef std::list<CATProtocolAction*> tATProtocolActions;
public:
	CCompositeAction(IActionExecutionContext& executionContext);
	virtual ~CCompositeAction();

	virtual void Execute();

private:
	CCompositeAction(const CCompositeAction&);
	CCompositeAction& operator=(const CCompositeAction&);

	tATProtocolActions m_actions;
};
}

