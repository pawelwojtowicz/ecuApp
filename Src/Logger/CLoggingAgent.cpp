#include "CLoggingAgent.h"
#include "CLogMsg.h"
#include "LoggerConst.h"
#include <UCL/CUnixDomainSocket.h>

namespace Logger
{
CLoggingAgent::CLoggingAgent(const std::string& unitQueueName)
: m_ownUnitQueueName(unitQueueName)
, m_loggerQueue(s_LoggerQueue)
{
	m_socket = new UCL::CUnixDomainSocket();
}

CLoggingAgent::~CLoggingAgent()
{
	delete m_socket;
}

void CLoggingAgent::Initialize(const UInt32& unitId)
{
	CLogMsg::SetLogAgent(this);
	CLogMsg::SetUnitId(unitId);
	CLogMsg::SetDebugLevel(0xFF);

	m_socket->Bind(m_ownUnitQueueName);
}

void CLoggingAgent::Shutdown()
{
	m_socket->Close();
}

void CLoggingAgent::IssueLog( const CLogMsg& msg )
{
	if ( m_socket->IsValid() )
	{
		Int8 logBuffer[MAX_LOGGER_MSG_SIZE];
		size_t msgSize(msg.Serialize(logBuffer));
  
		m_socket->Send(m_loggerQueue, logBuffer , msgSize);
	}
}

void CLoggingAgent::SetDebugLevel( const UInt32& debugLevel )
{
	CLogMsg::SetDebugLevel(debugLevel);
}


}
