#ifndef UCL_CSOCKET_H
#define UCL_CSOCKET_H

#include "GlobalTypes.h"

namespace UCL
{
class CSocket
{
	CSocket();
	virtual ~CSocket();
	
	bool Bind(const std::string& queueName);
	void Close();
	
	bool IsValid();
	
	
	

private:
	CSocket(const CSocket&);
	CSocket& operator=(const CSocket&);
	
	Int32 m_socketFileDescriptor;
	
	std::string m_socketName;

};

}

#endif
