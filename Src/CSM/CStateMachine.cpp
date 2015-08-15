#include "CStateMachine.h"
#include "IActionFactory.h"
#include "ICSMConfigurator.h"

namespace CSM
{

CStateMachine::CStateMachine()
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


void CStateMachine::AddState(	const std::string& parent, 
															const std::string& stateName, 
															const std::string& enterActionName, 
															const std::string& leafActionName, 
															const std::string& exitActioName)
{
}
	
void CStateMachine::AddTransition(	const std::string& eventName,
																		const std::string& sourceStateName, 
																		const std::string& destinationStateName, 
																		const std::string& conditionName, 
																		const std::string& actionName)
{
}

void CStateMachine::SetInitialState( const std::string& initialState)
{
}


bool CStateMachine::DispatchEvent( const std::string& eventName )
{
	return false;
}

}
