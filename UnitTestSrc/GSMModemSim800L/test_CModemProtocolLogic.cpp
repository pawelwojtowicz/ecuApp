#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../ATProtocolEngine/ATProtocolEngineTestMocks.h"
#include <GSMModemSim800L/CModemProtocolLogic.h>



class CModemProtocolLogicTest : public ::testing::Test
{
public:
	CModemProtocolLogicTest()
	: ModemProtocolLogic( mock_SerialPortHandler, mock_TimerManager)
	{
	};

	~CModemProtocolLogicTest()
	{
	};

	void SetUp()
	{
	};

	void TearDown()
	{
	};

	GSMModemSim800L::CModemProtocolLogic ModemProtocolLogic;

	TimerMock mock_TimerManager;

	CSerialPortHandlerMock mock_SerialPortHandler;
};
