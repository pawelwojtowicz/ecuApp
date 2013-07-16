#ifndef LOGGER_ILOGTARGET_H
#define LOGGER_ILOGTARGET_H

namespace Configuration
{
class CConfigNode;
}

namespace Logger
{
class CLogMsg;

class ILogTarget
{
public:
	ILogTarget() {};
	virtual ~ILogTarget() {};

	virtual bool Initialize(const Configuration::CConfigNode* pTargetConfiguration) = 0;
	virtual void Shutdown() = 0;

	virtual void LogToTarget(const CLogMsg& logMsg ) = 0;
private:
	ILogTarget(const ILogTarget&);
	ILogTarget& operator=(const ILogTarget&);
	
};
}
#endif
