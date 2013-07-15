#ifndef LOGGER_CLOGMANAGER_H
#define LOGGER_CLOGMANAGER_H
#include <mqueue.h>
#include <UCL/CThread.h>

namespace Logger
{
class CLogManager : public UCL::CThread
{
public:
	CLogManager();
	virtual ~CLogManager();
	
	void UpdateLoggerPrefixTable();

	bool Initialize();

	void Shutdown();

	virtual void Run();

private:
	//running flag - clear during shutdown
	bool m_running;

	//logger queue descriptor
	mqd_t m_loggerQueueDescriptor;
};
}
#endif
