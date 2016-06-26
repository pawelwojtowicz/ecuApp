#include "CUISOAPGateway.h"

uiSOAPGateway::CUISOAPGateway gs;

namespace uiSOAPGateway
{
  
 CUISOAPGateway::CUISOAPGateway()
    : Runtime::CExecutable(std::string("uiSOAPGateway"))
  {
  }

  CUISOAPGateway::~CUISOAPGateway()
  {
  }

  Int32 CUISOAPGateway::Run()
  {
		while(1)
		{
			printf("Calling - server Run()\n");
			m_server.run(8064);
		}
		return 0;
  }
}
