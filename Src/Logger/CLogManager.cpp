#include "CLogManager.h"
#include "LoggerConst.h"
#include "CLogMsg.h"

namespace Logger
{
CLogManager::CLogManager()
: m_running(true)
, m_loggerQueueDescriptor(-1)
{
}

CLogManager::~CLogManager()
{
}

bool CLogManager::Initialize()
{
	mq_attr queueAttributes;
	queueAttributes.mq_flags = 0;
	queueAttributes.mq_maxmsg = MAX_LOGGER_QUEUE_SIZE;
	queueAttributes.mq_msgsize = MAX_LOGGER_MSG_SIZE;

	m_loggerQueueDescriptor = mq_open( s_LoggerQueue , O_RDWR|O_CREAT, S_IRWXU, &queueAttributes);

	return ( -1 != m_loggerQueueDescriptor );
}

void CLogManager::Shutdown()
{
}

void CLogManager::Run()
{
	if ( -1 != m_loggerQueueDescriptor )
	{
		CLogMsg logMessage;
		Int8 logMsgBuffer[MAX_LOGGER_MSG_SIZE];
		Int32 logMsgSize(0);
		UInt32 priority(0);

		while ( m_running )
		{
			logMsgSize = mq_receive( m_loggerQueueDescriptor, (char*)logMsgBuffer, MAX_LOGGER_MSG_SIZE, &priority );

			if (logMessage.Deserialize(logMsgBuffer, logMsgSize ) )
			{
			}	
		}
	}
}

}
