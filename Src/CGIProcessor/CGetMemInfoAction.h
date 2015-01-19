#ifndef CGIPROCESSOR_CGetMemInfoAction_H
#define CGIPROCESSOR_CGetMemInfoAction_H
#include "IAction.h"

namespace CGIProcessor
{
class CProxyProvider;

class CGetMemInfoAction: public IAction
{
public:
  CGetMemInfoAction(CProxyProvider&);
  virtual ~CGetMemInfoAction() ;

  virtual bool Execute(const CEnvironment& variables, json::Object& commandOutput);

private:
  CGetMemInfoAction(const CGetMemInfoAction&);
  CGetMemInfoAction& operator=(const CGetMemInfoAction&);
};
}

#endif
