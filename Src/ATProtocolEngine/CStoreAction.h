#pragma once
#include "CATProtocolAction.h"

namespace ATProtocolEngine
{
class CStoreAction : public CATProtocolAction
{
/** Used Store(paramName)
		stores data incoming in the "recentLine" (ParamValue) of ParameterBundle, to the given paramName */
public:
	CStoreAction();
	virtual ~CStoreAction();

	virtual void Execute();

private:
	CStoreAction(const CStoreAction&);
	CStoreAction& operator=(const CStoreAction&);
};
}
