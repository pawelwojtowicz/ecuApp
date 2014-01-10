#ifndef CGIPROCESSOR_CControllerCommand_H
#define CGIPROCESSOR_CControllerCommand_H
#include "ICommand.h"
namespace Controller
{
class CControllerProxy;
}

namespace CGIProcessor
{
class CProxyProvider;

class CControllerCommand: public ICommand
{
public:
  CControllerCommand(CProxyProvider&);
  virtual ~CControllerCommand() {} ;

  virtual bool Execute(const CEnvironment& variables);

private:
  CControllerCommand(const CControllerCommand&);
  CControllerCommand& operator=(const CControllerCommand&);

  Controller::CControllerProxy* m_pControllerProxy;
};
}

#endif
