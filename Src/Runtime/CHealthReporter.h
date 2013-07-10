#ifndef RUNTIME_CHEALTHREPORTER_H
#define RUNTIME_CHEALTHREPORTER_H
#include "ITimerListener.h"
#include <ControllerInterface/ControllerTypes.h>

namespace Controller
{
class CControllerProxy;
}

namespace Runtime
{
class ITimerManager;

class CHealthReporter : public ITimerListener
{
public:
	CHealthReporter(ITimerManager& rTimerManager, Controller::CControllerProxy& rControllerProxy);
	virtual ~CHealthReporter();

	void Initialize( UInt32 runtimeUnitId, UInt32 heartbeatPeriod );
	void Shutdown();

	void ReportInitDone(const std::string& queueName, const std::string& versionInfo, const bool& status );

	void SetIddle();
	void SetBusy();
	void SetError();

private:
	virtual void NotifyTimer( const Int32& timerId );

private:
	CHealthReporter(const CHealthReporter&);
	CHealthReporter& operator=(const CHealthReporter&);

	ITimerManager& m_rTimerManager;

	Controller::CControllerProxy& m_rControllerProxy;

	Int32 m_heartbeatTimerId;

	UInt32 m_runtimeUnitId;

	Controller::tProcessStatus m_unitState;
};
}
#endif //RUNTIME_CHEALTHREPORTER_H
