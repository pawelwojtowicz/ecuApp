#ifndef CGIPROCESSOR_IACTION_H
#define CGIPROCESSOR_IACTION_H
#include <Global/GlobalTypes.h>

namespace CGIProcessor
{
class CEnvironment;

class IAction
{
public:
  IAction() {};
  virtual ~IAction() {};

  virtual bool Execute(const CEnvironment& environment) = 0;

private:
  IAction(const IAction&);
  IAction& operator=(const IAction&);
};
}

#endif
