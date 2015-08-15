#ifndef CSM_ICSMCONFIGURATOR_H
#define CSM_ICSMCONFIGURATOR_H

namespace CSM
{
class ICSMBuilder;

class ICSMConfigurator
{
public:
	ICSMConfigurator() {};
	virtual ~ICSMConfigurator() {};
	
	virtual bool InitializeStateMachine( ICSMBuilder* pBuilder ) = 0;

private:
	ICSMConfigurator(const ICSMConfigurator&);
	ICSMConfigurator& operator=(const ICSMConfigurator&);
};

}
#endif
