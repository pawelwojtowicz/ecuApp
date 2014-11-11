#ifndef CONTROLLER_ISessionStateListener_H
#define CONTROLLER_ISessionStateListener_H
#include <GlobalTypes.h>
#include <ControllerInterface/ControllerTypes.h>


namespace Controller
{
class ISessionStateListener
{
public:
	ISessionStateListener() {};
	virtual ~ISessionStateListener() {};
	
	virtual bool NotifySessionState(const tSessionState sessionState) = 0;
	
private:
	ISessionStateListener(const ISessionStateListener&);
	ISessionStateListener& operator=(const ISessionStateListener&);
};
}

#endif
