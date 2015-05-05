#ifndef RBCGATEWAY_CRBCGATEWAY_H
#define RBCGATEWAY_CRBCGATEWAY_H
#include <Runtime/CRuntimeUnit.h>
#include <UCL/CSerialPort.h>
#include "CRBCSendThread.h"

namespace RBCGateway
{
class CRBCGateway : public Runtime::CRuntimeUnit
{
public:
	CRBCGateway();
	virtual ~CRBCGateway();
	
  virtual void Initialize();

	virtual void Shutdown();
private:
	CRBCGateway(const CRBCGateway&);
	CRBCGateway& operator=(const CRBCGateway&);
	
	UCL::CSerialPort m_port;
	
	CRBCSendThread m_sendThread;	
};

}
#endif
