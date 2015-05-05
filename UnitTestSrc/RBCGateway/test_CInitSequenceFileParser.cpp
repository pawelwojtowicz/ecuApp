#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <RBCGateway/CInitSequenceFileParser.h>
#include <RBCGateway/CMsgBase.h>
#include <RBCGateway/IMsgFactory.h>
#include <RBCGateway/CMsgConfigurePID.h>
#include <GlobalTypes.h>

using ::testing::Return;

class MsgFactoryMock : public RBCGateway::IMsgFactory 
{
public:
	MOCK_METHOD1( CreateMessage, RBCGateway::CMsgBase* (const tStringVector arguments));
};


TEST( CInitSequenceFileParser, ParseFile )
{
	MsgFactoryMock factoryMock;
	tStringVector arguments;
	arguments.push_back("SetMotor");
	arguments.push_back("arg1");
	arguments.push_back("arg2");
	arguments.push_back("arg3");
	
	RBCGateway::CMsgBase* invalidMsgPointer = new RBCGateway::CMsgConfigurePID();
	
	std::string configFileName("test.txt");
	RBCGateway::CInitSequenceFileParser configParser(factoryMock);
	
	EXPECT_CALL( factoryMock, CreateMessage(arguments) ).Times(1).WillOnce(Return(invalidMsgPointer));

	RBCGateway::tMsgList initSequence = configParser.ParseFile(configFileName);
	
	EXPECT_EQ( initSequence.size() , 1);
}
