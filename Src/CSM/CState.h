#ifndef CSM_CSTATE_H
#define CSM_CSTATE_H
#include <GlobalTypes.h>

namespace CSM
{
class IAction;
class CTransition;

class CState
{
	typedef std::multimap<UInt32, CTransition*> tTransitionMap;
	typedef tTransitionMap::iterator tTranstionIterator;
	
public:
	CState( const std::string& stateName, IAction* enterAction, IAction* leafAction, IAction* exitAction);
	virtual ~CState();
	
	void AddTransition( CTransition* pTransition );
	
	const std::string& GetName() const;
	
	void ExecuteEnterAction();
	void ExecuteLeafAction();
	void ExecuteExitAction();

private:
	std::string m_stateName;
	
	IAction* m_pEnterAction;
	
	IAction* m_pLeafAction;
	
	IAction* m_pExitAction;	
};
}
#endif
