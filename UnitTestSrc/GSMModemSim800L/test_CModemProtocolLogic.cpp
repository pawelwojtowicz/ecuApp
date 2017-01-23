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
		GSMSim800LService.RegisterModemListener(&mock_ModemListener);

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
	EXPECT_CALL( mock_ModemListener			, NotifyModemManufacturerReceived("Wojtech") ).Times(1);
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+CGMM") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_ModemListener			, NotifyModemTypeReceived("MIG29") ).Times(1);
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+CGSN") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_ModemListener			, NotifyModemIMEIReceived("123456789") ).Times(1);
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+COPS?") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_ModemListener			, NotifyGSMProviderNameReceived("WojtechMobile") ).Times(1);

	GSMSim800LService.Connect();
	//AT
	ModemProtocolLogic.NotifyResponseReceived("OK");
	//AT+CLIP=1	
	ModemProtocolLogic.NotifyResponseReceived("OK");
	//AT+CMGF=1	
	ModemProtocolLogic.NotifyResponseReceived("OK");
	//AT+CSCS="GSM"	
	ModemProtocolLogic.NotifyResponseReceived("OK");
	//AT+CREG
	ModemProtocolLogic.NotifyResponseReceived("OK");
	//AT+CGMI
	ModemProtocolLogic.NotifyResponseReceived("Wojtech");
	ModemProtocolLogic.NotifyResponseReceived("OK");
	//AT+CGMM
	ModemProtocolLogic.NotifyResponseReceived("MIG29");
	ModemProtocolLogic.NotifyResponseReceived("OK");
	//imei
	ModemProtocolLogic.NotifyResponseReceived("123456789");
	ModemProtocolLogic.NotifyResponseReceived("OK");

	//AT+COPS?
	ModemProtocolLogic.NotifyResponseReceived("+COPS: 1,2,\"WojtechMobile\"");

	//ModemProtocolLogic.NotifyResponseReceived("OK");

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
	EXPECT_CALL( mock_ModemListener			, NotifyModemManufacturerReceived("Wojtech") ).Times(1);
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+CGMM") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_ModemListener			, NotifyModemTypeReceived("MIG29") ).Times(1);
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+CGSN") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_ModemListener			, NotifyModemIMEIReceived("123456789") ).Times(1);
	EXPECT_CALL( mock_SerialPortHandler , Test_SendCommand("AT+COPS?") ).Times(1).WillOnce(Return(true));
	EXPECT_CALL( mock_ModemListener			, NotifyGSMProviderNameReceived("WojtechMobile") ).Times(1);
	
	GSMSim800LService.Connect();
	//AT
	ModemProtocolLogic.NotifyResponseReceived("AT\rOK");
	//ATE0
	ModemProtocolLogic.NotifyResponseReceived("OK");
	//AT+CLIP=1
	ModemProtocolLogic.NotifyResponseReceived("OK");
	//AT+CMGF=1
	ModemProtocolLogic.NotifyResponseReceived("OK");
	//AT+CSCS=1
	ModemProtocolLogic.NotifyResponseReceived("OK");
	//AT+CREG=1
	ModemProtocolLogic.NotifyResponseReceived("OK");
	//AT+CGMI
	ModemProtocolLogic.NotifyResponseReceived("Wojtech");
	ModemProtocolLogic.NotifyResponseReceived("OK");
	//AT+CGMM
	ModemProtocolLogic.NotifyResponseReceived("MIG29");
	ModemProtocolLogic.NotifyResponseReceived("OK");
	//imei
	ModemProtocolLogic.NotifyResponseReceived("123456789");
	ModemProtocolLogic.NotifyResponseReceived("OK");

	//AT+COPS?
	ModemProtocolLogic.NotifyResponseReceived("+COPS: 1,2,\"WojtechMobile\"");
	//ModemProtocolLogic.NotifyResponseReceived("OK");

}
