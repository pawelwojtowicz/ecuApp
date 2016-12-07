#pragma once
#include <Global/GlobalTypes.h>
#include <CSM/IActionFactory.h>

namespace ATProtocolEngine
{
class IActionExecutionContext;
class CATProtocolAction;

class CATProtocolActionFactory: public CSM::IActionFactory
{
	typedef std::map<std::string, CSM::IAction*> tNameToActionMap;
public:
	CATProtocolActionFactory(IActionExecutionContext& rExecutionContext);
	virtual ~CATProtocolActionFactory();

private:
	/** Implementation of CSM::IActionFactory */
	virtual CSM::IAction* GetAction( const std::string& actionName ) const;
	virtual CSM::ICondition* GetCondition( const std::string& conditionName) const;

private:
	CATProtocolAction* CreateActionInstance( const std::string& actionName ) const;

private:
	IActionExecutionContext& m_rActionExecutionContext;
};
}
