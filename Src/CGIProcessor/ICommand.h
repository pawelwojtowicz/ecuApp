#ifndef CGIPROCESSOR_ICOMMAND_H
#define CGIPROCESSOR_ICOMMAND_H
#include <Global/GlobalTypes.h>

namespace CGIProcessor
{
class ICommand
{
public:
  ICommand() {};
  virtual ~ICommand() {};

  virtual bool Execute(const tVariablesMap& variables) = 0;

private:
  ICommand(const ICommand&);
  ICommand& operator=(const ICommand&);
};
}

#endif
