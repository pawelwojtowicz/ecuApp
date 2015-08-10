#ifndef CSM_CTRANSITION_H
#define CSM_CTRANSITION_H
#include <GlobalTypes.h>

namespace CSM
{
class IAction;
class ICondition;

class CTransition
{
public:
	CTransition( const std::string& name, ICondition* pCondition, IAction* pAction);
	virtual ~CTransition();
	
	bool CanExecute();
	
	void ExecuteAction();
	
private:
	std::string m_eventName;

	ICondition* m_pCondition;
	
	IAction* m_pAction;
};

}
#endif
