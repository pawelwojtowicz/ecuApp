#ifndef CGIPROCESSOR_IACTION_H
#define CGIPROCESSOR_IACTION_H
#include <Global/GlobalTypes.h>

namespace json
{
class Object;
}

namespace CGIProcessor
{
class CEnvironment;

class IAction
{
public:
  IAction() {};
  virtual ~IAction() {};

  virtual bool Execute(const CEnvironment& environment, json::Object& commandOutput) = 0;

private:
  IAction(const IAction&);
  IAction& operator=(const IAction&);
};
}

#endif
