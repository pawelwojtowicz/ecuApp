#ifndef LOGGER_CLOGGINGAGENT_H
#define LOGGER_CLOGGINGAGENT_H
#include "ILogAgent.h"
#include <mqueue.h>
#include <GlobalTypes.h>
namespace Logger
{
class CLoggingAgent : public ILogAgent
{
public:
	CLoggingAgent();
	virtual ~CLoggingAgent();

	void Initialize(const UInt32& unitId);

	void Shutdown();

	void SetDebugLevel( const UInt32& debugLevel );

	virtual void IssueLog( const CLogMsg& msg );

private:

	//logger queue descriptor
	mqd_t m_loggerQueueDescriptor;
};
}
#endif
