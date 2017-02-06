#pragma once
#include "CATProtocolAction.h"

namespace ATProtocolEngine
{
class CSetParamAction : public CATProtocolAction
{
/** Used setParam(paramName, paramValue)
		stores paramValue under the name of paramName */
public:
	CSetParamAction(IActionExecutionContext& actionExecutionContext);
	virtual ~CSetParamAction();

	virtual bool Configure(const CSM::IActionFactory& , const std::string& configurationString);

	virtual void Execute();

private:
	CSetParamAction(const CSetParamAction&);
	CSetParamAction& operator=(const CSetParamAction&);

	std::string m_paramName;
	std::string m_paramValue;
};
}
