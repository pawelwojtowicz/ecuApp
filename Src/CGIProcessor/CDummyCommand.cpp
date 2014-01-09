#include "CDummyCommand.h"
#include <stdio.h>

namespace CGIProcessor
{

int CDummyCommand::i = 0;

bool CDummyCommand::Execute(const tVariablesMap& variables)
{
  printf("Dziala madafaka %d\n", i);
  return false;
}
}
