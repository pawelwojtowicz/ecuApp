#ifndef LOGGER_ILOGAGENT_H
#define LOGGER_ILOGAGENT_H
namespace Logger
{
class CLogMsg;

class ILogAgent
{
public:
	ILogAgent() {};
	virtual ~ILogAgent() {};
	
	virtual void IssueLog( const CLogMsg& msg ) = 0;

private:
	ILogAgent(const ILogAgent&);
	ILogAgent& operator=(const ILogAgent&);
};
}
#endif
