#ifndef CSM_ICSMBUILDER_H
#define CSM_ICSMBUILDER_H
#include <GlobalTypes.h>

namespace CSM
{
class ICSMBuilder
{
protected:
	ICSMBuilder() {};
	virtual ~ICSMBuilder() {};
	
public:
	virtual void AddState(const std::string& parent, 
												const std::string& stateName, 
												const std::string& enterActionName, 
												const std::string& leafActionName, 
												const std::string& exitActioName) = 0;
	
	virtual void AddTransition(	const std::string& sourceStateName, 
															const std::string& destinationStateName, 
															const std::string& conditionName, 
															const std::string& actionName) = 0;
	
private:
	ICSMBuilder(const ICSMBuilder&);
	ICSMBuilder& operator=( const ICSMBuilder&);
};
}


#endif
