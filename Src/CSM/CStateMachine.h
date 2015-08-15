#ifndef CSM_CSTATEMACHINE_H
#define CSM_CSTATEMACHINE_H
#include "ICSMBuilder.h"

namespace CSM
{

class IActionFactory;
class ICSMConfigurator;

class CStateMachine : public ICSMBuilder
{
public:
	CStateMachine();
	virtual ~CStateMachine();
	
	bool Initialize( ICSMConfigurator* pConfigurator, IActionFactory* pFactory);
	
	bool DispatchEvent( const std::string& eventName );

private:

	/** implementation of CSM::ICSMBuilder */
	virtual void AddState(const std::string& parent, 
												const std::string& stateName, 
												const std::string& enterActionName, 
												const std::string& leafActionName, 
												const std::string& exitActioName);
	
	virtual void AddTransition(	const std::string& eventName,
															const std::string& sourceStateName, 
															const std::string& destinationStateName, 
															const std::string& conditionName, 
															const std::string& actionName);
	
private:
	CStateMachine(const CStateMachine&);
	CStateMachine& operator=(const CStateMachine&);
};
}

#endif
