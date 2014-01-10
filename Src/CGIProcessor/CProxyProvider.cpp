#include "CProxyProvider.h"
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
