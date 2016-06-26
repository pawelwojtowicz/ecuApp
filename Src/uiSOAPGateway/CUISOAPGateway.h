#ifndef UISOAPGATEWAY_CUISOAPGATEWAY_H
#define UISOAPGATEWAY_CUISOAPGATEWAY_H

#include <Runtime/CExecutable.h>

namespace uiSOAPGateway
{
  class CUISOAPGateway: public Runtime::CExecutable
{
  CUISOAPGateway();
  virtual ~CUISOAPGateway();

private:
  virtual Int32 Run();

private:

};
}

#endif
