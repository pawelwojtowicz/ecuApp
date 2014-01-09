#ifndef CGIPROCESSOR_CDUMMYCOMMAND_H
#define CGIPROCESSOR_CDUMMYCOMMAND_H
#include "ICommand.h"

namespace CGIProcessor
{
class CDummyCommand: public ICommand
{
public:
  CDummyCommand() { ++i;} ;
  virtual ~CDummyCommand() {} ;

  virtual bool Execute(const tVariablesMap& variables);

private:
  CDummyCommand(const CDummyCommand&);
  CDummyCommand& operator=(const CDummyCommand&);

  static int i;
};
}

#endif
