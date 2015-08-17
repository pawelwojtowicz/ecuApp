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
	CState( CState* pParentState, const std::string& stateName, IAction* enterAction, IAction* leafAction, IAction* exitAction);
	virtual ~CState();
	
	void UpdateState(CState* pParentState, IAction* enterAction, IAction* leafAction, IAction* exitAction);
	
	
	const std::string& GetName() const;
	
	const CState* GetParent() const;
	
	void ExecuteEnterAction();
	void ExecuteLeafAction();
	void ExecuteExitAction();
	
	
	void AddTransition( const UInt32 eventNameHash, CTransition* pTransition );
	
	CTransition* GetTransition( const UInt32 eventNameHash );

private:
	CState* m_pParentState;

	std::string m_stateName;
	
	IAction* m_pEnterAction;
	
	IAction* m_pLeafAction;
	
	IAction* m_pExitAction;
	
	tTransitionMap m_nameHashToTransitionMap;
};
}
#endif
