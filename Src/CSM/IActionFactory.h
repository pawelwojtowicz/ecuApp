#ifndef CSM_IACTIONFACTORY_H
#define CSM_IACTIONFACTORY_H
#include <GlobalTypes.h>

namespace CSM
{
class IAction;
class ICondition;

class IActionFactory
{
protected:
	IActionFactory() {};
	virtual ~IActionFactory() {};

public:
	virtual IAction* GetAction( const std::string& actionName ) = 0 ;
	
	virtual ICondition* GetCondition( const std::string& conditionName) = 0;
	
private:
	IActionFactory(const IActionFactory&);
	IActionFactory& operator=(const IActionFactory&);
};

}
#endif
