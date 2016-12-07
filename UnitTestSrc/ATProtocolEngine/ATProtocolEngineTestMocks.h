#include <ATProtocolEngine/ISerialPortHandler.h>
#include <ATProtocolEngine/IActionExecutionContext.h>
#include <ATProtocolEngine/CParameterBundle.h>
#include <ATProtocolEngine/ISerializationEngine.h>

using ::testing::EndsWith;


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
		std::string output = bundle.GetParameter(std::string("outputValue"));
		msgText = output;
		if (!bundle.GetParameter("status").compare("true") )
		{
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
	ActionContextMock(ATProtocolEngine::ISerialPortHandler& portHandler, 
										ATProtocolEngine::CParameterBundle& paramBundle,
										ATProtocolEngine::ISerializationEngine& serializationEngine )
	: m_serialPortHandlerMock(portHandler)
	, m_parameterBundle(paramBundle)
	, m_serializationEngine(serializationEngine)
	{
	}

	virtual ATProtocolEngine::ISerializationEngine& GetSerializationEngine() { return m_serializationEngine;};

	virtual ATProtocolEngine::ISerialPortHandler& GetSerialPortHandler() {return m_serialPortHandlerMock;};

	virtual ATProtocolEngine::CParameterBundle& GetParameterBundle() { return m_parameterBundle;};

private:
	ATProtocolEngine::ISerialPortHandler& m_serialPortHandlerMock;

	ATProtocolEngine::CParameterBundle& m_parameterBundle;

	ATProtocolEngine::ISerializationEngine& m_serializationEngine;
	
};
