#ifndef LOGGER_CLOGGINGAGENT_H
#define LOGGER_CLOGGINGAGENT_H
#include "ILogAgent.h"
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

	virtual void IssueLog( const CLogMsg& msg );

private:

};
}
#endif
