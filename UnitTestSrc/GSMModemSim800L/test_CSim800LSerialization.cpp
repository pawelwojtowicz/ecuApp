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
