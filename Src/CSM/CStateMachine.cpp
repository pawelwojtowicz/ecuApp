#include "CStateMachine.h"
#include "IActionFactory.h"
#include "ICSMConfigurator.h"
#include "IAction.h"
#include "CState.h"
#include "CTransition.h"
#include <UCL/CFastHash.h>
namespace CSM
{
static const UInt32 cUInt32_CSM_HashSeed = 0x11FF;


CStateMachine::CStateMachine()
: m_pActionFactory(0)
, m_pCurrentState(0)
{
}

CStateMachine::~CStateMachine()
{
}
	
bool CStateMachine::Initialize( ICSMConfigurator* pConfigurator, IActionFactory* pFactory)
{
	if ( 0!= pConfigurator )
	{
		return pConfigurator->InitializeStateMachine(this);
	}
	return false;
}


void CStateMachine::AddState(	const std::string& parentName, 
															const std::string& stateName, 
															const std::string& enterActionName, 
															const std::string& leafActionName, 
															const std::string& exitActioName)
{
	CState* pParentState(0);
	
	IAction* pEnterAction(0);
	IAction* pLeafAction(0);
	IAction* pExitAction(0);
	
	UInt32 parentNameHash(UCL::CFastHash::CalculateHash32(parentName, cUInt32_CSM_HashSeed));
	UInt32 stateNameHash(UCL::CFastHash::CalculateHash32(stateName, cUInt32_CSM_HashSeed));
	
	if ( 0 != m_pActionFactory )
	{
		if ( !enterActionName.empty() )
		{
			pEnterAction = m_pActionFactory->GetAction(enterActionName);
		}
		
		if ( !leafActionName.empty() )
		{
			pLeafAction = m_pActionFactory->GetAction(leafActionName);
		}
		
		if ( !exitActioName.empty() )
		{
			pExitAction = m_pActionFactory->GetAction(exitActioName);
		}
	}

	tStateMapIterator parentStateIterator( m_stateMap.find(parentNameHash) );
	if ( m_stateMap.end() != parentStateIterator )
	{
		pParentState = parentStateIterator->second;
	}
	else
	{
		pParentState = new CState( 0 , stateName, 0 , 0, 0 );
		
		m_stateMap.insert( tStateMap::value_type(parentNameHash,pParentState));
	}
	
	tStateMapIterator stateIterator(m_stateMap.find(stateNameHash));
	if ( m_stateMap.end() == stateIterator )
	{
		CState* pState = new CState( pParentState, stateName, pEnterAction, pLeafAction, pExitAction );
		m_stateMap.insert( tStateMap::value_type(stateNameHash,pState));

	}
	else
	{
		stateIterator->second->UpdateState(pParentState, pEnterAction, pLeafAction, pExitAction);
	}
}
	
void CStateMachine::AddTransition(	const std::string& eventName,
																		const std::string& sourceStateName, 
																		const std::string& targetStateName, 
																		const std::string& conditionName, 
																		const std::string& actionName)
{
	UInt32 eventNameHash(UCL::CFastHash::CalculateHash32(eventName, cUInt32_CSM_HashSeed));
	UInt32 sourceNameHash(UCL::CFastHash::CalculateHash32(sourceStateName, cUInt32_CSM_HashSeed));
	UInt32 targetNameHash(UCL::CFastHash::CalculateHash32(targetStateName, cUInt32_CSM_HashSeed));
	
	CState* pSourceState(0);
	CState* pTargetState(0);
	IAction* pTransitionAction(0);
	ICondition* pTransitionCondition(0);
	
	tStateMapConstIterator pSourceStateIter(m_stateMap.find(sourceNameHash));
	if ( m_stateMap.end() != pSourceStateIter )
	{
		pSourceState = pSourceStateIter->second;
	}
	
	tStateMapConstIterator pTargetStateIter(m_stateMap.find(targetNameHash));
	if ( m_stateMap.end() != pTargetStateIter )
	{
		pTargetState = pTargetStateIter->second;
	}
	
	if ( 0 != pSourceState && 0 != pTargetState )
	{
		if ( 0 !=m_pActionFactory )
		{
			if ( !conditionName.empty() )
			{
				pTransitionCondition = m_pActionFactory->GetCondition(conditionName);
			}
		
			if ( !actionName.empty() )
			{
				pTransitionAction = m_pActionFactory->GetAction(actionName);
			}
		}
		
		CTransition* pTransition = new CTransition( eventName , 
																								pTransitionCondition, 
																								pTransitionAction, 
																								pTargetState);
																								
		pSourceState->AddTransition( eventNameHash , pTransition );
	}
}

void CStateMachine::SetInitialState( const std::string& initialState)
{
	UInt32 initialStateNameHash(UCL::CFastHash::CalculateHash32(initialState, cUInt32_CSM_HashSeed));
	
	tStateMapConstIterator pInitialStateIter(m_stateMap.find(initialStateNameHash));
	if ( m_stateMap.end() != pInitialStateIter )
	{
		m_pCurrentState = pInitialStateIter->second;
	}

}


bool CStateMachine::DispatchEvent( const std::string& eventName )
{
	return false;
}

}
