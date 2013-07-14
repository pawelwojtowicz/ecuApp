#include "CLoggingAgent.h"
#include "CLogMsg.h"
#include <stdio.h>

namespace Logger
{
CLoggingAgent::CLoggingAgent()
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
}

void CLoggingAgent::Shutdown()
{
}

void CLoggingAgent::IssueLog( const CLogMsg& msg )
{
	 msg.ToString();
}

}
