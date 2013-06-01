#ifndef CONTROLLER_CCONTROLLERSTUB_H
#define CONTROLLER_CCONTROLLERSTUB_H

namespace Controller
{

class CControllerStub
{
public:
	CControllerStub( Runtime::IMessenger& rMessenger );
	virtual ~CControllerStub();

	virtual bool Initialize();
	virtual bool Shutdown();

private:
	IRuntime::IMessenger& m_messenger;
};

}
#endif //CONTROLLER_CONTROLLERSTUB_H
