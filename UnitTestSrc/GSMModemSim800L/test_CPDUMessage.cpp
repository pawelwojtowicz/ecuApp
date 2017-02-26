#include <gtest/gtest.h>

#include <GSMModemSim800L/CPDUMessage.h>

std::string message("07918406026080F3040B918496063787F50000712031913481408C54747A0E4ACF41F6B23C0F62BFDD67D0BC3D6781EEE8F4180DBA87E7A079D94D0799E5EF36A89D07B5DFE234BBEC0225E9A07B9ACD0689CBA0FABC4C06A5DDA0BA3B4D07D1CB73FA1C447F83C6E8F2186D4F9B41547419342FCBD361765A1FA6D7DF6ED03D3C07A5DB7076B95D76D3CB64D0F82D9797C77476DE05");

TEST( CPDUMessage, noPayload )
{
	GSMModemSim800L::CPDUMessage pduMessage;
	ASSERT_FALSE ( pduMessage.IsValid() );
}

TEST( CPDUMessage, Deserialize )
{
	GSMModemSim800L::CPDUMessage pduMessage;

	ASSERT_TRUE ( pduMessage.Deserialize(message) );
	ASSERT_TRUE ( pduMessage.IsValid() );
	EXPECT_EQ ( pduMessage.GetServiceCenterNumber() , std::string("+48602006083") );
	EXPECT_EQ ( pduMessage.GetSenderNumber() , 				std::string("+48696073785") );
}

