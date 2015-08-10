#include "CTransition.h"
#include "IAction.h"
#include "ICondition.h" 

namespace CSM
{

CTransition::CTransition( const std::string& name, ICondition* pCondition, IAction* pAction)
:	m_eventName(name)
, m_pCondition(pCondition)
, m_pAction(pAction)
{
}

CTransition::~CTransition()
{
}
	
bool CTransition::CanExecute()
{
	if ( 0 != m_pCondition )
	{
		return m_pCondition->Evaluate();
	}
	
	return true;
}
	
void CTransition::ExecuteAction()
{
	if ( 0 != m_pAction )
	{
		m_pAction->Execute();
	}
}

}

