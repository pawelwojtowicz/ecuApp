#ifndef LOGGER_CSYSLOGTARGET_H
#define LOGGER_CSYSLOGTARGET_H
#include "ILogTarget.h"

namespace Logger
{

class CSyslogTarget: public ILogTarget
{
public:
	CSyslogTarget();
	virtual ~CSyslogTarget();

	virtual bool Initialize(const Configuration::CConfigNode* pTargetConfiguration);
	virtual void Shutdown();

	virtual void LogToTarget(const CLogMsg& logMsg );

private:
	CSyslogTarget(const CSyslogTarget&);
	CSyslogTarget& operator=(const CSyslogTarget&);
};

}
#endif
