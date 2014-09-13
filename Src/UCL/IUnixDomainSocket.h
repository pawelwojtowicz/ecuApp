#ifndef UCL_IUnixDomainSocket_H
#define UCL_IUnixDomainSocket_H

#include "GlobalTypes.h"

namespace UCL
{
class CSocketAddress;

class IUnixDomainSocket
{
public:
	IUnixDomainSocket() {} ;
	virtual ~IUnixDomainSocket() {} ;
	
	virtual bool Bind(const std::string& queueName) = 0;
	virtual void Close() = 0;
	
	virtual bool IsValid() = 0;
	
	virtual bool IsEmpty() = 0;
	
	virtual Int32 Send(CSocketAddress& sockAddress, Int8* buffer, const Int32& bytestToSend) = 0;
	virtual Int32 Receive(CSocketAddress& sockAddress, Int8* buffer, const Int32& bytestToSend) = 0;

private:
	IUnixDomainSocket(const IUnixDomainSocket&);
	IUnixDomainSocket& operator=(const IUnixDomainSocket&);
};

}

#endif
