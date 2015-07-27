#include "CState.h"
#include "IAction.h"
#include "CTransition.h"

namespace CSM
{
CState::CState( const std::string& stateName, IAction* enterAction, IAction* leafAction, IAction* exitAction)
: m_stateName(stateName)
, m_pEnterAction(enterAction)
, m_pLeafAction(leafAction)
, m_pExitAction(exitAction)	
{
}
	
CState::~CState()
{
}
	
const std::string& CState::GetName() const
{
	return m_stateName;
}

void CState::AddTransition( CTransition* pTransition )
{
}
	
void CState::ExecuteEnterAction()
{
	if ( 0 != m_pEnterAction )
	{
		m_pEnterAction->Execute();
	}
}

void CState::ExecuteLeafAction()
{
	if ( 0 != m_pLeafAction )
	{
		m_pLeafAction->Execute();
	}
}

void CState::ExecuteExitAction()
{
	if ( 0 != m_pExitAction )
	{
		m_pExitAction->Execute();
	}
}

}
