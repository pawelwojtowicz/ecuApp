#ifndef LOGGER_ILOGTARGET_H
#define LOGGER_ILOGTARGET_H

namespace Configuration
{
class CConfigNode;
}

namespace Logger
{
class ILogTarget
{
public:
	ILogTarget() {};
	virtual ~ILogTarget() {};

	virtual bool Initialize(const Configuration::CConfigNode* pTargetConfiguration);
	virtual void Shutdown();

	virtual void LogToTarget(const CLogMsg& logMsg ) = 0;
private:
	ILogTarget(const ILogTarget&);
	ILogTarget& operator=(const ILogTarget&);
	
};
}
#endif
