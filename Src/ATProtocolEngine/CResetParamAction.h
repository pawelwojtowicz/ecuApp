#pragma once
#include "CATProtocolAction.h"

namespace ATProtocolEngine
{
class CResetParamAction : public CATProtocolAction
{
/** Used Store(paramName)
		stores data incoming in the "recentLine" (ParamValue) of ParameterBundle, to the given paramName */
public:
	CResetParamAction(IActionExecutionContext& actionExecutionContext);
	virtual ~CResetParamAction();

	virtual bool Configure(const CSM::IActionFactory& , const std::string& configurationString);

	virtual void Execute();

private:
	CResetParamAction(const CResetParamAction&);
	CResetParamAction& operator=(const CResetParamAction&);

	std::string m_paramName;
};
}
