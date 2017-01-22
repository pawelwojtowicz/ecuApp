#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../ATProtocolEngine/ATProtocolEngineTestMocks.h"
#include <GSMModemSim800L/CModemProtocolLogic.h>
#include "GSMActionContextMocks.h"



class CModemProtocolLogicTest : public ::testing::Test
{
public:
	CModemProtocolLogicTest()
	: ModemProtocolLogic( mock_SerialPortHandler, mock_TimerManager)
	, GSMSim800LService(ModemProtocolLogic)
	{
	};

	~CModemProtocolLogicTest()
	{
	};

	void SetUp()
	{
		GSMSim800LService.Initialize(mock_configuration);
	};

	void TearDown()
	{
	};

	GSMModemSim800L::CModemProtocolLogic ModemProtocolLogic;
	GSMDaemon::IGSMModemService& GSMSim800LService;

	TimerMock mock_TimerManager;

	CSerialPortHandlerMock mock_SerialPortHandler;

	GSMConfiguration mock_configuration;
};

TEST_F( CModemProtocolLogicTest , Basic )
{
}
