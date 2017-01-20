#include <gtest/gtest.h>

#include <ATProtocolEngine/CParameterBundle.h>
#include <GSMModemSim800L/CSim800LSerialization.h>
#include <GSMModemSim800L/GSMModemSim800LConst.h>

TEST( CSim800LSerialization, RX_RawData )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_DATA"), receiver.Deserialize(std::string("TheseAreNotRecognizedData"), paramBundle) );
	ASSERT_TRUE ( paramBundle.IsAvailable("DATA") );
	EXPECT_EQ ( std::string("TheseAreNotRecognizedData"), paramBundle.GetParameter("DATA") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RX_OK )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_OK"), receiver.Deserialize(std::string("OK"), paramBundle) );
	ASSERT_FALSE ( paramBundle.IsAvailable("DATA") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RX_RING )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_INCOMING_CALL"), receiver.Deserialize(std::string("RING"), paramBundle) );
	ASSERT_FALSE ( paramBundle.IsAvailable("DATA") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RX_BUSY )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_BUSY"), receiver.Deserialize(std::string("BUSY"), paramBundle) );
	ASSERT_FALSE ( paramBundle.IsAvailable("DATA") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RX_NO_DIALTONE )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_NO_DIALTONE"), receiver.Deserialize(std::string("NO DIALTONE"), paramBundle) );
	ASSERT_FALSE ( paramBundle.IsAvailable("DATA") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RX_NO_CARRIER )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_NO_CARRIER"), receiver.Deserialize(std::string("NO CARRIER"), paramBundle) );
	ASSERT_FALSE ( paramBundle.IsAvailable("DATA") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RX_NO_ANSWER )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_NO_ANSWER"), receiver.Deserialize(std::string("NO ANSWER"), paramBundle) );
	ASSERT_FALSE ( paramBundle.IsAvailable("DATA") );

	serializationEngine.Shutdown();
}


TEST( CSim800LSerialization, RX_CPIN )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_SIM_STATUS"), receiver.Deserialize(std::string("+CPIN: SIM PUK"), paramBundle) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CPIN_simStatus) );
	EXPECT_EQ (std::string("SIM PUK"), paramBundle.GetParameter(GSMModemSim800L::sc_CPIN_simStatus) );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RX_CREG )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_REG_STATE"), receiver.Deserialize(std::string("+CREG: 1,2"), paramBundle) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CREG_regStatus) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CREG_regStatus) );
	EXPECT_EQ (std::string("1"), paramBundle.GetParameter(GSMModemSim800L::sc_CREG_regMode) );
	EXPECT_EQ (std::string("2"), paramBundle.GetParameter(GSMModemSim800L::sc_CREG_regStatus) );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RX_CREG_with_Location_info )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_REG_STATE"), receiver.Deserialize(std::string("+CREG: 4,3,2,1"), paramBundle) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CREG_regStatus) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CREG_regStatus) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CREG_lac) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CREG_ci) );
	EXPECT_EQ (std::string("4"), paramBundle.GetParameter(GSMModemSim800L::sc_CREG_regMode) );
	EXPECT_EQ (std::string("3"), paramBundle.GetParameter(GSMModemSim800L::sc_CREG_regStatus) );
	EXPECT_EQ (std::string("2"), paramBundle.GetParameter(GSMModemSim800L::sc_CREG_lac) );
	EXPECT_EQ (std::string("1"), paramBundle.GetParameter(GSMModemSim800L::sc_CREG_ci) );

	serializationEngine.Shutdown();
}


TEST( CSim800LSerialization, RX_CMGL )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_SMS_DETAILS"), receiver.Deserialize(std::string("+CMGL: 2,\"REC UNREAD\",\"+69123456789\",\"\",\"2016-03-23\""), paramBundle) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CMGL_msgId) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CMGL_msgState) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CMGL_msgOrgNo) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CMGL_msgOrgNoTxt) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CMGL_msgTimeStamp ) );
	EXPECT_EQ (std::string("2"), paramBundle.GetParameter(GSMModemSim800L::sc_CMGL_msgId) );
	EXPECT_EQ (std::string("REC UNREAD"), paramBundle.GetParameter(GSMModemSim800L::sc_CMGL_msgState) );
	EXPECT_EQ (std::string("+69123456789"), paramBundle.GetParameter(GSMModemSim800L::sc_CMGL_msgOrgNo) );
	EXPECT_EQ (std::string(""), paramBundle.GetParameter(GSMModemSim800L::sc_CMGL_msgOrgNoTxt) );
	EXPECT_EQ (std::string("2016-03-23"), paramBundle.GetParameter(GSMModemSim800L::sc_CMGL_msgTimeStamp) );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RX_CLIP )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_CALLER_IDENTIFICATION"), receiver.Deserialize(std::string("+CLIP: \"+48696073786\",145,\"subadr\",,\"alphaID\",0"), paramBundle) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CLIP_number ) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CLIP_type) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CLIP_subaddr) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CLIP_hrNumber ));
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CLIP_alphaID ));
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CLIP_cliValidity) );
	EXPECT_EQ (std::string("+48696073786"), paramBundle.GetParameter(GSMModemSim800L::sc_CLIP_number) );
	EXPECT_EQ (std::string("145"), paramBundle.GetParameter(GSMModemSim800L::sc_CLIP_type) );
	EXPECT_EQ (std::string("subadr"), paramBundle.GetParameter(GSMModemSim800L::sc_CLIP_subaddr) );
	EXPECT_EQ (std::string(""), paramBundle.GetParameter(GSMModemSim800L::sc_CLIP_hrNumber) );
	EXPECT_EQ (std::string("alphaID"), paramBundle.GetParameter(GSMModemSim800L::sc_CLIP_alphaID) );
	EXPECT_EQ (std::string("0"), paramBundle.GetParameter(GSMModemSim800L::sc_CLIP_cliValidity) );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RX_CME_ERROR )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_ERROR"), receiver.Deserialize(std::string("+CME ERROR: 123"), paramBundle) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CME_errorCode) );
	EXPECT_EQ (std::string("123"), paramBundle.GetParameter(GSMModemSim800L::sc_CME_errorCode) );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RX_CMTI )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_NEW_SMS_RECEIVED"), receiver.Deserialize(std::string("+CMTI: \"SM\",2"), paramBundle) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CMTI_memoryKind) );
	ASSERT_TRUE ( paramBundle.IsAvailable(GSMModemSim800L::sc_CMTI_index) );
	EXPECT_EQ (std::string("SM"), paramBundle.GetParameter(GSMModemSim800L::sc_CMTI_memoryKind) );
	EXPECT_EQ (std::string("2"), paramBundle.GetParameter(GSMModemSim800L::sc_CMTI_index) );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, TX_CMGS )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ATProtocolEngine::ISerializationEngine& transmitterSerialization(serializationEngine);

	paramBundle.Store(GSMModemSim800L::sc_CMGS_trgtNumber,"+48796073785");
	paramBundle.Store(GSMModemSim800L::sc_CMGS_msgText,"This is an example of the SMS");

	std::string serializationOutput;

	ASSERT_TRUE( transmitterSerialization.SerializeMsg("CMGS", paramBundle, serializationOutput ) );
	EXPECT_EQ( std::string("AT+CMGS=\"+48796073785\"\rThis is an example of the SMS\x1A"), serializationOutput );
}

TEST( CSim800LSerialization, TX_ATD )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ATProtocolEngine::ISerializationEngine& transmitterSerialization(serializationEngine);

	paramBundle.Store(GSMModemSim800L::sc_ATD_trgtNumber,"+48796073785");
	std::string serializationOutput;

	ASSERT_TRUE( transmitterSerialization.SerializeMsg("ATD", paramBundle, serializationOutput ) );
	EXPECT_EQ( std::string("ATD+48796073785;"), serializationOutput );
}

TEST( CSim800LSerialization, TX_CPIN )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ATProtocolEngine::ISerializationEngine& transmitterSerialization(serializationEngine);

	paramBundle.Store(GSMModemSim800L::sc_CPIN_pin,"4312");
	std::string serializationOutput;

	ASSERT_TRUE( transmitterSerialization.SerializeMsg("CPIN", paramBundle, serializationOutput ) );
	EXPECT_EQ( std::string("AT+CPIN=\"4312\""), serializationOutput );
}

