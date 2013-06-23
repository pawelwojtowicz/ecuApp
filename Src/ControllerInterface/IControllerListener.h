#ifndef CONTROLLER_ICONTROLLERLISTENER_H
#define CONTROLLER_ICONTROLLERLISTENER_H

namespace Controller
{
class IControllerListener
{
public:
	IControllerListener() {};
	virtual ~IControllerListener() {};

	virtual void NotifyShutdownPending() = 0;

	virtual void ShutdownProcess() = 0;

private:
	IControllerListener(const IControllerListener&);
	IControllerListener& operator=(const IControllerListener&);
};
}
#endif
