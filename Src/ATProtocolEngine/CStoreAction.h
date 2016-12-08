#pragma once
#include "CATProtocolAction.h"

namespace ATProtocolEngine
{
class CStoreAction : public CATProtocolAction
{
/** Used Store(paramName)
		stores data incoming in the "recentLine" (ParamValue) of ParameterBundle, to the given paramName */
public:
	CStoreAction(IActionExecutionContext& actionExecutionContext);
	virtual ~CStoreAction();

	virtual bool Configure(const CSM::IActionFactory& , const std::string& configurationString);

	virtual void Execute();

private:
	CStoreAction(const CStoreAction&);
	CStoreAction& operator=(const CStoreAction&);

	std::string m_inputParam;
	std::string m_outputParam;
};
}
