#pragma once
#include <Global/GlobalTypes.h>
#include <CSM/IActionFactory.h>

namespace ATProtocolEngine
{
class CATProtocolAction;

class CATProtocolActionFactory: public CSM::IActionFactory
{
	typedef std::map<std::string, CSM::IAction*> tNameToActionMap;
public:
	CATProtocolActionFactory();
	virtual ~CATProtocolActionFactory();

	void RegisterAction( const std::string& actionName, CATProtocolAction* pAction );

private:
	virtual CSM::IAction* GetAction( const std::string& actionName ) const;
	
	virtual CSM::ICondition* GetCondition( const std::string& conditionName) const;

private:
	tNameToActionMap m_nameToActionMap;
};
}
