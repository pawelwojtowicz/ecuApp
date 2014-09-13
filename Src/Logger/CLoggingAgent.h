#ifndef LOGGER_CLOGGINGAGENT_H
#define LOGGER_CLOGGINGAGENT_H
#include "ILogAgent.h"
#include <GlobalTypes.h>
#include <UCL/CUnixDomainSocket.h>


namespace Logger
{
class CLoggingAgent : public ILogAgent
{
public:
	CLoggingAgent(const std::string& unitQueueName);
	virtual ~CLoggingAgent();

	void Initialize(const UInt32& unitId);

	void Shutdown();

	void SetDebugLevel( const UInt32& debugLevel );

	virtual void IssueLog( const CLogMsg& msg );

private:
	UCL::CSocketAddress m_loggerQueue;

	UCL::IUnixDomainSocket* m_socket;
	
	std::string m_ownUnitQueueName;
};

}
#endif
