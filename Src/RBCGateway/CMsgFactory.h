#ifndef RBCGATEWAY_CMSGFACTORY_H
#define RBCGATEWAY_CMSGFACTORY_H
#include "IMsgFactory.h"

namespace RBCGateway
{
class CMsgFactory : public IMsgFactory
{
public:
	CMsgFactory() {} ;
	virtual ~CMsgFactory() {};
	
	virtual CMsgBase* CreateMessage(tStringVector arguments);
	
private:
	CMsgFactory(const CMsgFactory&);
	CMsgFactory& operator=(const CMsgFactory&);
};
}
#endif
