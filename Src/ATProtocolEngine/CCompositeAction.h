#pragma once
#include "CATProtocolAction.h"
#include <list>

namespace ATProtocolEngine
{
class CCompositeAction : public CATProtocolAction
{
/** Used when the action line consist of many actions separated by ;
		Actions will be executed one after another. */

	typedef std::list<CSM::IAction*> tATProtocolActions;
public:
	CCompositeAction(IActionExecutionContext& executionContext);
	virtual ~CCompositeAction();

	virtual bool Configure( const CSM::IActionFactory& rFactory,const std::string& configurationString );

	virtual void Execute();

private:
	CCompositeAction(const CCompositeAction&);
	CCompositeAction& operator=(const CCompositeAction&);

	tATProtocolActions m_actions;
};
}

