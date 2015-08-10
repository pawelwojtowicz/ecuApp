#ifndef CSM_CARGOCONFIGURATOR_H
#define CSM_CARGOCONFIGURATOR_H
#include <GlobalTypes.h>

namespace CSM
{
class IActionFactory;
class ICSMBuilder;

class CArgoConfigurator
{
public:
	CArgoConfigurator();
	virtual ~CArgoConfigurator();
	
	bool InitializeStateMachine(const std::string& stateMachineFileName ,
															ICSMBuilder* pBuilder,
															IActionFactory* pActionFactory );
	
public:
	CArgoConfigurator(const CArgoConfigurator&);
	CArgoConfigurator& operator=(const CArgoConfigurator&);
};
}
#endif
