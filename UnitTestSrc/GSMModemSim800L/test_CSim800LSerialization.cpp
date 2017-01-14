#include <gtest/gtest.h>

#include <ATProtocolEngine/CParameterBundle.h>
#include <GSMModemSim800L/CSim800LSerialization.h>

TEST( CSim800LSerialization, RawData )
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

TEST( CSim800LSerialization, OK )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_OK"), receiver.Deserialize(std::string("OK"), paramBundle) );
	ASSERT_FALSE ( paramBundle.IsAvailable("DATA") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, RING )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_INCOMING_CALL"), receiver.Deserialize(std::string("RING"), paramBundle) );
	ASSERT_FALSE ( paramBundle.IsAvailable("DATA") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, BUSY )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_BUSY"), receiver.Deserialize(std::string("BUSY"), paramBundle) );
	ASSERT_FALSE ( paramBundle.IsAvailable("DATA") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, NO_DIALTONE )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_NO_DIALTONE"), receiver.Deserialize(std::string("NO DIALTONE"), paramBundle) );
	ASSERT_FALSE ( paramBundle.IsAvailable("DATA") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, NO_CARRIER )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_NO_CARRIER"), receiver.Deserialize(std::string("NO CARRIER"), paramBundle) );
	ASSERT_FALSE ( paramBundle.IsAvailable("DATA") );

	serializationEngine.Shutdown();
}

TEST( CSim800LSerialization, NO_ANSWER )
{
	ATProtocolEngine::CParameterBundle paramBundle;
	GSMModemSim800L::CSim800LSerialization serializationEngine;
	ASSERT_TRUE( serializationEngine.Initialize() );

	ATProtocolEngine::ISerializationEngine& receiver(serializationEngine);

	EXPECT_EQ (std::string("E_NO_ANSWER"), receiver.Deserialize(std::string("NO ANSWER"), paramBundle) );
	ASSERT_FALSE ( paramBundle.IsAvailable("DATA") );

	serializationEngine.Shutdown();
}


TEST( CSim800LSerialization, CPIN )
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

TEST( CSim800LSerialization, CREG )
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

TEST( CSim800LSerialization, CREG_with_Location_info )
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


TEST( CSim800LSerialization, CMGL )
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

TEST( CSim800LSerialization, CLIP )
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
