#ifndef CGIPROCESSOR_CONTROLLERACTION_H
#define CGIPROCESSOR_CControllerAction_H
#include "IAction.h"
namespace Controller
{
class CControllerProxy;
}

namespace CGIProcessor
{
class CProxyProvider;

class CControllerAction: public IAction
{
public:
  CControllerAction(CProxyProvider&);
  virtual ~CControllerAction() {} ;

  virtual bool Execute(const CEnvironment& variables, json::Object& commandOutput);

private:
  CControllerAction(const CControllerAction&);
  CControllerAction& operator=(const CControllerAction&);

  Controller::CControllerProxy* m_pControllerProxy;
};
}

#endif
