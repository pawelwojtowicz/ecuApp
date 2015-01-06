#include "CSyslogTarget.h"
#include "Logger.h"
#include "CLogMsg.h"
#include <syslog.h>
namespace Logger
{
CSyslogTarget::CSyslogTarget()
{
}

CSyslogTarget::~CSyslogTarget()
{
}

bool CSyslogTarget::Initialize(const Configuration::CConfigNode* pTargetConfiguration)
{
	return true;
}

void CSyslogTarget::Shutdown()
{
}

void CSyslogTarget::LogToTarget(const CLogMsg& logMsg )
{	
	UInt32 syslogDBGzone(0);
	
	switch ( logMsg.GetDebugZone() )
	{
	case ERROR:
		{
			syslogDBGzone = LOG_ERR;
		};break;
	case WARNING:
		{
			syslogDBGzone = LOG_WARNING;
		};break;
	case INFO:
	case DATA:

		{
			syslogDBGzone = LOG_INFO;
		};break;
	case DET1:
	case DET2:
		{
			syslogDBGzone = LOG_DEBUG;
		};break;
	default:
		{
			syslogDBGzone = LOG_ERR;		
		};
	}
	
	syslog(LOG_MAKEPRI( LOG_USER , syslogDBGzone), logMsg.GetEntryText() );
}

}
