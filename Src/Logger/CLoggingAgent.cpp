#include "CLoggingAgent.h"
#include "CLogMsg.h"
#include "LoggerConst.h"

namespace Logger
{
CLoggingAgent::CLoggingAgent()
:	m_loggerQueueDescriptor(-1)
{
}
CLoggingAgent::~CLoggingAgent()
{
}

void CLoggingAgent::Initialize(const UInt32& unitId)
{
	CLogMsg::SetLogAgent(this);
	CLogMsg::SetUnitId(unitId);
	CLogMsg::SetDebugLevel(0xFF);

	m_loggerQueueDescriptor = mq_open( s_LoggerQueue , O_WRONLY|O_NONBLOCK, S_IRWXU, 0);
}

void CLoggingAgent::Shutdown()
{
	mq_close(m_loggerQueueDescriptor);
}

void CLoggingAgent::IssueLog( const CLogMsg& msg )
{
	if (-1 != m_loggerQueueDescriptor )
	{
		Int8 logBuffer[MAX_LOGGER_MSG_SIZE];
		size_t msgSize(msg.Serialize(logBuffer));
  
		mq_send( m_loggerQueueDescriptor , logBuffer , msgSize, 0 );
	}
}

void CLoggingAgent::SetDebugLevel( const UInt32& debugLevel )
{
	CLogMsg::SetDebugLevel(debugLevel);
}


}
