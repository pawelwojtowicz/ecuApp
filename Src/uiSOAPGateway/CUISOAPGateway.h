#ifndef UISOAPGATEWAY_CUISOAPGATEWAY_H
#define UISOAPGATEWAY_CUISOAPGATEWAY_H

#include <Runtime/CExecutable.h>
#include "CDataServiceSOAPStub.h"

namespace uiSOAPGateway
{
class CUISOAPGateway: public Runtime::CExecutable
{
public:
  CUISOAPGateway();
  virtual ~CUISOAPGateway();
private:
  virtual Int32 Run();

private:
	CDataServiceSOAPStub m_server;

};
}

#endif
