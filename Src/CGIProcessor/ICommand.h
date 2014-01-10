#ifndef CGIPROCESSOR_ICOMMAND_H
#define CGIPROCESSOR_ICOMMAND_H
#include <Global/GlobalTypes.h>

namespace CGIProcessor
{
class CEnvironment;

class ICommand
{
public:
  ICommand() {};
  virtual ~ICommand() {};

  virtual bool Execute(const CEnvironment& environment) = 0;

private:
  ICommand(const ICommand&);
  ICommand& operator=(const ICommand&);
};
}

#endif
