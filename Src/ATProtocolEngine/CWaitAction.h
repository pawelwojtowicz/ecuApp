#pragma once
#include "CATProtocolAction.h"

namespace ATProtocolEngine
{
class CWaitAction : public CATProtocolAction
{
/** Wait action - introduces a sleep for a given amount of ms. */
public:
	CWaitAction(IActionExecutionContext& actionExecutionContext);
	virtual ~CWaitAction();

	virtual bool Configure(const CSM::IActionFactory& , const std::string& configurationString);

	virtual void Execute();

private:
	CWaitAction(const CWaitAction&);
	CWaitAction& operator=(const CWaitAction&);

	UInt32 m_microseconds;
};
}
