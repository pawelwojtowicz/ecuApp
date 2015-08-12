#ifndef CSM_CARGOCONFIGURATOR_H
#define CSM_CARGOCONFIGURATOR_H
#include <GlobalTypes.h>

class XMLNode; 

namespace CSM
{
class IActionFactory;
class ICSMBuilder;

class CArgoConfigurator
{
	struct sState
	{
		std::string ParentName;
		std::string StateName;
		std::string EnterActionName;
		std::string LeafActionName;
		std::string ExitActionName;
	};
	
	typedef std::map<std::string, sState> tIdToState;
	typedef tIdToState::const_iterator tIdToStateConstIterator;

	typedef std::map<std::string, std::string> tIdToNameMap;
	typedef tIdToNameMap::const_iterator tIdToNameMapConstIterator;
	
public:
	CArgoConfigurator();
	virtual ~CArgoConfigurator();
	
	bool InitializeStateMachine( 	const std::string& stateMachineFileName , 
																const std::string& stateMachineName, 
																ICSMBuilder* pBuilder );
																
private:
	void ReadCompositeStateConfiguration ( const std::string& parentName, const XMLNode& stateConfigNode );
	const std::string ReadActionConfiguration( const XMLNode& actionConfiguration );
	void ConfigureTransitions( const XMLNode& transitions);
public:
	CArgoConfigurator(const CArgoConfigurator&);
	CArgoConfigurator& operator=(const CArgoConfigurator&);
	
	tIdToState m_statesMap;
	
	tIdToNameMap m_IdToNameMap;
};
}
#endif
