#ifndef RBCGATEWAY_IMSGFACTORY_H
#define RBCGATEWAY_IMSGFACTORY_H
#include <GlobalTypes.h>

namespace RBCGateway
{
class CMsgBase;

class IMsgFactory
{
public:
	IMsgFactory() {} ;
	virtual ~IMsgFactory() {};
	
	virtual CMsgBase* CreateMessage(tStringVector arguments) = 0;
	
private:
	IMsgFactory( const IMsgFactory&);
	IMsgFactory& operator=(const IMsgFactory&);
};
}
#endif
