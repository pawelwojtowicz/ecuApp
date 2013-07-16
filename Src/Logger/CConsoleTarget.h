#ifndef LOGGER_CCONSOLETARGET_H
#define LOGGER_CCONSOLETARGET_H
#include "ILogTarget.h"

namespace Logger
{

class CConsoleTarget: public ILogTarget
{
public:
	CConsoleTarget();
	virtual ~CConsoleTarget();

	virtual bool Initialize(const Configuration::CConfigNode* pTargetConfiguration);
	virtual void Shutdown();

	virtual void LogToTarget(const CLogMsg& logMsg );

private:
	CConsoleTarget(const CConsoleTarget&);
	CConsoleTarget& operator=(const CConsoleTarget&);
};

}
#endif
