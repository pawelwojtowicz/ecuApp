#include <gtest/gtest.h>

#include <ATProtocolEngine/CParameterBundle.h>
#include <GSMModemSim800L/CSim800LSerialization.h>

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
	ASSERT_TRUE ( paramBundle.IsAvailable("SIMSTATUS") );
	EXPECT_EQ (std::string("SIM PUK"), paramBundle.GetParameter("SIMSTATUS") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RX_CREG )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_REG_STATE"), receiver.Deserialize(std::string("+CREG: 1,2"), paramBundle) );
	ASSERT_TRUE ( paramBundle.IsAvailable("REG_MODE") );
	ASSERT_TRUE ( paramBundle.IsAvailable("REG_STATE") );
	EXPECT_EQ (std::string("1"), paramBundle.GetParameter("REG_MODE") );
	EXPECT_EQ (std::string("2"), paramBundle.GetParameter("REG_STATE") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RX_CREG_with_Location_info )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_REG_STATE"), receiver.Deserialize(std::string("+CREG: 4,3,2,1"), paramBundle) );
	ASSERT_TRUE ( paramBundle.IsAvailable("REG_MODE") );
	ASSERT_TRUE ( paramBundle.IsAvailable("REG_STATE") );
	ASSERT_TRUE ( paramBundle.IsAvailable("LAC") );
	ASSERT_TRUE ( paramBundle.IsAvailable("CI") );
	EXPECT_EQ (std::string("4"), paramBundle.GetParameter("REG_MODE") );
	EXPECT_EQ (std::string("3"), paramBundle.GetParameter("REG_STATE") );
	EXPECT_EQ (std::string("2"), paramBundle.GetParameter("LAC") );
	EXPECT_EQ (std::string("1"), paramBundle.GetParameter("CI") );

	serializationEngine.Shutdown();
}


TEST( CSim800LSerialization, RX_CMGL )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_SMS_DETAILS"), receiver.Deserialize(std::string("+CMGL: 2,\"REC UNREAD\",\"+69123456789\",\"\",\"2016-03-23\""), paramBundle) );
	ASSERT_TRUE ( paramBundle.IsAvailable("MSG_ID") );
	ASSERT_TRUE ( paramBundle.IsAvailable("MSG_STATE") );
	ASSERT_TRUE ( paramBundle.IsAvailable("PHONE_NUMBER") );
	ASSERT_TRUE ( paramBundle.IsAvailable("PHONE_NUMBER_NAME") );
	ASSERT_TRUE ( paramBundle.IsAvailable("MSG_TIMESTAMP") );
	EXPECT_EQ (std::string("2"), paramBundle.GetParameter("MSG_ID") );
	EXPECT_EQ (std::string("REC UNREAD"), paramBundle.GetParameter("MSG_STATE") );
	EXPECT_EQ (std::string("+69123456789"), paramBundle.GetParameter("PHONE_NUMBER") );
	EXPECT_EQ (std::string(""), paramBundle.GetParameter("PHONE_NUMBER_NAME") );
	EXPECT_EQ (std::string("2016-03-23"), paramBundle.GetParameter("MSG_TIMESTAMP") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RX_CLIP )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_CALLER_IDENTIFICATION"), receiver.Deserialize(std::string("+CLIP: \"+48696073786\",145,\"subadr\",,\"alphaID\",0"), paramBundle) );
	ASSERT_TRUE ( paramBundle.IsAvailable("NUMBER") );
	ASSERT_TRUE ( paramBundle.IsAvailable("TYPE") );
	ASSERT_TRUE ( paramBundle.IsAvailable("SUBADDR") );
	ASSERT_TRUE ( paramBundle.IsAvailable("SATYPE") );
	ASSERT_TRUE ( paramBundle.IsAvailable("ALPHA_ID") );
	ASSERT_TRUE ( paramBundle.IsAvailable("CLI_VALIDITY") );
	EXPECT_EQ (std::string("+48696073786"), paramBundle.GetParameter("NUMBER") );
	EXPECT_EQ (std::string("145"), paramBundle.GetParameter("TYPE") );
	EXPECT_EQ (std::string("subadr"), paramBundle.GetParameter("SUBADDR") );
	EXPECT_EQ (std::string(""), paramBundle.GetParameter("SATYPE") );
	EXPECT_EQ (std::string("alphaID"), paramBundle.GetParameter("ALPHA_ID") );
	EXPECT_EQ (std::string("0"), paramBundle.GetParameter("CLI_VALIDITY") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RX_CME_ERROR )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_ERROR"), receiver.Deserialize(std::string("+CME ERROR: 123"), paramBundle) );
	ASSERT_TRUE ( paramBundle.IsAvailable("ERROR_CODE") );
	EXPECT_EQ (std::string("123"), paramBundle.GetParameter("ERROR_CODE") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RX_CMTI )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_NEW_SMS_RECEIVED"), receiver.Deserialize(std::string("+CMTI: \"SM\",2"), paramBundle) );
	ASSERT_TRUE ( paramBundle.IsAvailable("MEMORY") );
	ASSERT_TRUE ( paramBundle.IsAvailable("INDEX") );
	EXPECT_EQ (std::string("SM"), paramBundle.GetParameter("MEMORY") );
	EXPECT_EQ (std::string("2"), paramBundle.GetParameter("INDEX") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, TX_CMGS )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ATProtocolEngine::ISerializationEngine& transmitterSerialization(serializationEngine);

	paramBundle.Store("NUMBER","+48796073785");
	paramBundle.Store("TEXT","This is an example of the SMS");

	std::string serializationOutput;

	ASSERT_TRUE( transmitterSerialization.SerializeMsg("CMGS", paramBundle, serializationOutput ) );
	EXPECT_EQ( std::string("AT+CMGS=\"+48796073785\"\rThis is an example of the SMS\x1A"), serializationOutput );
}

TEST( CSim800LSerialization, TX_ATD )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ATProtocolEngine::ISerializationEngine& transmitterSerialization(serializationEngine);

	paramBundle.Store("NUMBER","+48796073785");
	std::string serializationOutput;

	ASSERT_TRUE( transmitterSerialization.SerializeMsg("ATD", paramBundle, serializationOutput ) );
	EXPECT_EQ( std::string("ATD+48796073785;"), serializationOutput );
}

TEST( CSim800LSerialization, TX_CPIN )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ATProtocolEngine::ISerializationEngine& transmitterSerialization(serializationEngine);

	paramBundle.Store("PIN","4312");
	std::string serializationOutput;

	ASSERT_TRUE( transmitterSerialization.SerializeMsg("CPIN", paramBundle, serializationOutput ) );
	EXPECT_EQ( std::string("AT+CPIN=\"4312\""), serializationOutput );
}

