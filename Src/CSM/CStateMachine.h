#ifndef CSM_CSTATEMACHINE_H
#define CSM_CSTATEMACHINE_H
#include <GlobalTypes.h>
#include "ICSMBuilder.h"

namespace CSM
{

class IActionFactory;
class ICSMConfigurator;
class CState;

class CStateMachine : public ICSMBuilder
{
	typedef std::map<UInt32, CState*> tStateMap;
	typedef tStateMap::const_iterator tStateMapConstIterator;
	typedef tStateMap::iterator tStateMapIterator;
	
	typedef std::list<CState*> tStateList;
	typedef tStateList::iterator tStateListIterator;
	typedef tStateList::reverse_iterator tStateListReverseIterator;
	
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
															
	virtual void SetInitialState( const std::string& initialState);
	
private:
	bool DispatchEvent( const UInt32 eventNameHash );

	
private:
	CStateMachine(const CStateMachine&);
	CStateMachine& operator=(const CStateMachine&);
	
	IActionFactory* m_pActionFactory;
	
	tStateMap m_stateMap;
	
	CState* m_pCurrentState;
};
}

#endif
