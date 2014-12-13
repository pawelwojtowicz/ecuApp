#include "CProxyProvider.h"
#include <unistd.h>
#include <ControllerInterface/CControllerProxy.h>


namespace CGIProcessor
{

CProxyProvider::CProxyProvider()
: m_controllerProxy(0)
{
}

CProxyProvider::~CProxyProvider()
{
  if ( 0!=m_controllerProxy)
  {
    delete m_controllerProxy;
  }
}

bool CProxyProvider::Initialize()
{
	pid_t processID = getpid();
	
	char queueName[50];
	
	sprintf(queueName, "cgiProcessor%d",static_cast<UInt32>(processID));
	
	return m_messenger.Initialize(std::string(queueName));
}

void CProxyProvider::Shutdown()
{
	m_messenger.Shutdown();
}


Controller::CControllerProxy* CProxyProvider::GetControllerProxy()
{
  if ( 0 == m_controllerProxy )
  {
    m_controllerProxy = new Controller::CControllerProxy(m_messenger);
    if ( 0 != m_controllerProxy )
    {
      m_controllerProxy->Initialize(0);
    }
  }

  return m_controllerProxy;
}

}
