#ifndef CONTROLLERMOCKS_H
#define CONTROLLERMOCKS_H

#include <Runtime/ITimerManager.h>
#include <Runtime/ITimerListener.h>
#include <Controller/ISessionStateListener.h>
#include <Controller/ISessionManager.h>
#include <Controller/IProcessControl.h>
#include <ControllerInterface/IProcessStatusReporter.h>
#include <ControllerInterface/CPublicProcessInfo.h>

namespace ControllerTest
{
class TimerManagerMock : public Runtime::ITimerManager
{
public:
		// creates a timer - returns unique timerId
	MOCK_METHOD1(CreateTimer, Int32( Runtime::ITimerListener* timerListener ));

	// destroys the timer, given by the timerId
	MOCK_METHOD1(DisposeTimer, void(const Int32 timerId ));	

	// sets the parameters for the timer, given by timerId
	MOCK_METHOD3(SetTimer, bool( const Int32 timerId, const UInt32 delay, const UInt32 period));
	
	// Starts the timer, given by the Id
	MOCK_METHOD1(StartTimer, bool(const Int32 timerId ) );
	
	// Stops the timer, given by the Id	
	MOCK_METHOD1(StopTimer, bool(const Int32 timerId) );
	
	// Gets the current tickout of the system
	MOCK_METHOD0(GetCurrentTime, const UInt32());

};

class SessionStateListenerMock: public Controller::ISessionStateListener
{
public:
	MOCK_METHOD1(NotifySessionState, bool(const Controller::tSessionState sessionState));
};

class SessionManagerMock: public Controller::ISessionManager
{
public:
	MOCK_METHOD1( RegisterSessionListener, Int32( Controller::ISessionStateListener* pListener ) );
	
	MOCK_METHOD2(	ReportItemState, void(const Int32& itemId,const bool busy ) );
};

class ProcessControlMock: public Controller::IProcessControl
{
public:
	MOCK_METHOD4(	AddProcessController, bool(	UInt32 processID, 
																			std::string executableName,
																			UInt32 heartbeatPeriod,
																			UInt32 debugZoneSetting) );
	
	MOCK_METHOD1( StartProcess, void( Int32 processHandlerID ) );
	
	MOCK_METHOD1( TerminateProcess, void( Int32 processHandlerID ) );
};

class ProcessorStatusReporterMock: public Controller::IProcessStatusReporter
{
public:
	MOCK_METHOD2( SendProcessStatus, bool(const UInt32 processId, const Controller::tProcessStatus& status ) );

	MOCK_METHOD1( PublishProcessInfo, bool ( Controller::CPublicProcessInfo& processInfo));
};
}

#endif
