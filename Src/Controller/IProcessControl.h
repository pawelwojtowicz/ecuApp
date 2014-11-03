#ifndef CONTROLLER_IPROCESSCONTROL_H
#define CONTROLLER_IPROCESSCONTROL_H

namespace Controller
{
class IProcessControl
{
public:
	void StartProcess( const Int32& processHandlerID ) = 0;
	
	void TerminateProcess( const Int32& processHandlerID ) = 0;

private:
	IProcessControl(const IProcessControl&);
	IProcessControl& operator=(const IProcessControl&);
};
}
#endif //CONTROLLER_IPROCESSCONTROL_H
