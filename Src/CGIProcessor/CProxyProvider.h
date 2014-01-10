#ifndef CGIPROCESSOR_CPROXYPROVIDER_H
#define CGIPROCESSOR_CPROXYPROVIDER_H
#include <Runtime/CMessenger.h>
#include <ControllerInterface/CControllerProxy.h>

namespace Controller
{
class CControllerProxy;
}

namespace CGIProcessor
{
class CProxyProvider
{
public:
  CProxyProvider();
  virtual ~CProxyProvider();

  Controller::CControllerProxy* GetControllerProxy();

private:
  CProxyProvider(const CProxyProvider&);
  CProxyProvider& operator=(const CProxyProvider&);

  Runtime::CMessenger m_messenger;

  Controller::CControllerProxy* m_controllerProxy;
};
}

#endif
