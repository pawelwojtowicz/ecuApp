#include "CRBCGateway.h"
#include <Logger/Logger.h>

RBCGateway::CRBCGateway gs;

namespace RBCGateway
{
CRBCGateway::CRBCGateway()
: Runtime::CRuntimeUnit("RBCGateway", "rbcGateway_Q")
, m_port()
{
}

CRBCGateway::~CRBCGateway()
{
}
	
void CRBCGateway::Initialize()
{
// important - initialize the messenger
  CRuntimeUnit::Initialize();

// important - initialize the timer manager
  InitializeTimerManager();
  
  std::string portName("/dev/ttyAMA0");
  std::string configuration("baud=19200 data=8 parity=none stop=2");
  if (m_port.Open(portName))
  {
  
  	if ( m_port.Configure(configuration) )
  	{
  		char tmp[] = {"Test Stringa"};
  		m_port.Write(tmp, 12); 
  	}
  	else
  	{
  		RETAILMSG(ERROR,("Failed to configure the port"));
  	}
  	
  }
  else
  {
  	RETAILMSG(INFO, ("Failed to open the port"));
  }
  InitDone(true);
}

void CRBCGateway::Shutdown()
{
}

}
