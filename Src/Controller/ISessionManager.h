#ifndef CONTROLLER_ISESSIONMANAGER_H
#define CONTROLLER_ISESSIONMANAGER_H
#include <GlobalTypes.h>
#include <ControllerInterface/ControllerTypes.h>

namespace Controller
{
class ISessionStateListener;

class ISessionManager
{
public:
	ISessionManager() {};
	virtual ~ISessionManager() {};
	
	virtual Int32 RegisterSessionListener( ISessionStateListener* pListener ) = 0;
	
	virtual void ReportItemState(const Int32& itemId,const bool busy ) = 0;

private:
	ISessionManager& operator=(const ISessionManager&);
	ISessionManager(const ISessionManager&);
};

}
#endif //CONTROLLER_ISESSIONMANAGER_H
