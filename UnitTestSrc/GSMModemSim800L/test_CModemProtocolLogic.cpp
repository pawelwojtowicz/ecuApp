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
		EXPECT_CALL( mock_TimerManager , CreateTimer(NotNull()) ).Times(2).WillOnce(Return(1)).WillOnce(Return(2));
		EXPECT_CALL( mock_TimerManager , SetTimer( 2, 0, 30 ) ).Times(1);
		EXPECT_CALL( mock_TimerManager , StartTimer( 2 ) ).Times(1);
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

	ModemListenerMock mock_ModemListener;
};

TEST_F( CModemProtocolLogicTest , Connect_ModemCheck_WithNoEcho )
{
	EXPECT_CALL( mock_SerialPortHandler , OpenPort() ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_SerialPortHandler , StartProcessing() ).Times(1);
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+CLIP=1") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+CMGF=1") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+CSCS=\"GSM\"") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+CREG=1") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+CGMI") ).Times(1).WillOnce(Return(true));
	GSMSim800LService.Connect();
	ModemProtocolLogic.NotifyResponseReceived("OK");
	ModemProtocolLogic.NotifyResponseReceived("OK");
	ModemProtocolLogic.NotifyResponseReceived("OK");
	ModemProtocolLogic.NotifyResponseReceived("OK");
	ModemProtocolLogic.NotifyResponseReceived("OK");
}

TEST_F( CModemProtocolLogicTest , Connect_ModemCheck_WithEcho )
{
	EXPECT_CALL( mock_SerialPortHandler , OpenPort() ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_SerialPortHandler , StartProcessing() ).Times(1);
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("ATE0") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+CLIP=1") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+CMGF=1") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+CSCS=\"GSM\"") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+CREG=1") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+CGMI") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+CGMM") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+CGSN") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_ModemListener			, NotifyModemIMEIReceived("123456789") ).Times(1);
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+COPS?") ).Times(1).WillOnce(Return(true));
	
	GSMSim800LService.Connect();
	ModemProtocolLogic.NotifyResponseReceived("AT\rOK");
	ModemProtocolLogic.NotifyResponseReceived("OK");
	ModemProtocolLogic.NotifyResponseReceived("OK");
	ModemProtocolLogic.NotifyResponseReceived("OK");
	ModemProtocolLogic.NotifyResponseReceived("OK");
	ModemProtocolLogic.NotifyResponseReceived("OK");
	ModemProtocolLogic.NotifyResponseReceived("OK");
	ModemProtocolLogic.NotifyResponseReceived("OK");
	//imei
	ModemProtocolLogic.NotifyResponseReceived("123456789");
	ModemProtocolLogic.NotifyResponseReceived("OK");

}
