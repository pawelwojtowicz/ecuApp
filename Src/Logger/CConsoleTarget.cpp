#include "CConsoleTarget.h"
#include <Configuration/CConfiguration.h>
#include "CLogMsg.h"
#include <stdio.h>
namespace Logger
{
CConsoleTarget::CConsoleTarget()
{
}

CConsoleTarget::~CConsoleTarget()
{
}

bool CConsoleTarget::Initialize(const Configuration::CConfigNode* pTargetConfiguration)
{
	return true;
}

void CConsoleTarget::Shutdown()
{
}

void CConsoleTarget::LogToTarget(const CLogMsg& logMsg )
{
	logMsg.ToString();
}

}
