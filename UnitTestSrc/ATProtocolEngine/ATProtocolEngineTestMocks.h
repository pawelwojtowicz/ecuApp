#pragma once
#include <ATProtocolEngine/IResponseTimeoutHandler.h>
#include <ATProtocolEngine/ISerialPortHandler.h>
#include <ATProtocolEngine/IActionExecutionContext.h>
#include <ATProtocolEngine/CParameterBundle.h>
#include <ATProtocolEngine/ISerializationEngine.h>
#include <Runtime/ITimerManager.h>
#include <Runtime/ITimerListener.h>

using ::testing::Return;
using ::testing::EndsWith;

class CTimeoutHandlerMock: public ATProtocolEngine::IResponseTimeoutHandler
{
public:
	MOCK_METHOD1( StartTimeout, void( UInt32 timeout ) );
	MOCK_METHOD0( StopTimeout, void() );
};



class CSerialPortHandlerMock : public ATProtocolEngine::ISerialPortHandler
{
public:
		bool SendCommand( const std::string& atCommand )
		{
			return Test_SendCommand(atCommand);	
		};
		MOCK_METHOD1(Test_SendCommand, bool(std::string atResponse) );
};


class CSerializationEngineMock: public ATProtocolEngine::ISerializationEngine
{
public:
	bool SerializeMsg( const std::string& msgId, const ATProtocolEngine::CParameterBundle& bundle, std::string& msgText )
	{
		SerializeMsgID = msgId;

		if ( bundle.IsAvailable(std::string("outputValue")) && bundle.IsAvailable("status") )
		{
			std::string output = bundle.GetParameter(std::string("outputValue"));
			msgText = output;
			if (!bundle.GetParameter("status").compare("true") )
			{
				return true;
			}
		}		
		else if (!msgId.compare("REG"))
		{
			msgText = std::string("AT+REG");
			return true;
		}
		return false;
	}

	const std::string Deserialize( const std::string& inputData, ATProtocolEngine::CParameterBundle& bundle)
	{
		DeserializationInputData = inputData;
		bundle.Store("outputValue", inputData);
		return inputData;
	}

	std::string SerializeMsgID;
	std::string DeserializationInputData;
};


class ActionContextMock : public ATProtocolEngine::IActionExecutionContext
{
public:
	ActionContextMock(ATProtocolEngine::IResponseTimeoutHandler& timeoutHandler,
										ATProtocolEngine::ISerialPortHandler& portHandler, 
										ATProtocolEngine::CParameterBundle& paramBundle,
										ATProtocolEngine::ISerializationEngine& serializationEngine )
	: m_TimeoutHandler(timeoutHandler)
	, m_serialPortHandlerMock(portHandler)
	, m_parameterBundle(paramBundle)
	, m_serializationEngine(serializationEngine)
	{
	}

	virtual ATProtocolEngine::IResponseTimeoutHandler& GetTimeoutHandler() { return m_TimeoutHandler; };

	virtual ATProtocolEngine::ISerializationEngine& GetSerializationEngine() { return m_serializationEngine;};

	virtual ATProtocolEngine::ISerialPortHandler& GetSerialPortHandler() {return m_serialPortHandlerMock;};

	virtual ATProtocolEngine::CParameterBundle& GetParameterBundle() { return m_parameterBundle;};

private:
	ATProtocolEngine::IResponseTimeoutHandler& m_TimeoutHandler;

	ATProtocolEngine::ISerialPortHandler& m_serialPortHandlerMock;

	ATProtocolEngine::CParameterBundle& m_parameterBundle;

	ATProtocolEngine::ISerializationEngine& m_serializationEngine;
	
};


class TimerMock: public Runtime::ITimerManager
{
public:
	MOCK_METHOD1( CreateTimer , Int32(Runtime::ITimerListener* timerListener) );
	MOCK_METHOD1( DisposeTimer, void(const Int32 timerId ) );	
	MOCK_METHOD3( SetTimer, bool( const Int32 timerId, const UInt32 delay, const UInt32 period) );
	MOCK_METHOD1( StartTimer, bool (const Int32 timerId ) );
	MOCK_METHOD1( StopTimer, bool(const Int32 timerId) );
	MOCK_METHOD0( GetCurrentTime, const UInt32() );
};
