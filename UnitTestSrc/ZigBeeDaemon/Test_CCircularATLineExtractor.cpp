#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ZigBeeDaemon/CCircularATLineExtractor.h>
#include <ZigBeeDaemon/IATLineConsumer.h>

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::EndsWith;
using ::testing::NotNull;
using ::testing::InSequence;
using ::testing::_;


class ATLineConsumerMock : public ZigBeeDaemon::IATLineConsumer
{
public:
	ATLineConsumerMock(){};
	virtual ~ATLineConsumerMock(){};

	MOCK_METHOD1(NotifyATResponseExtracted, void(const std::string atResponse) );
	MOCK_METHOD1(NotifyATPromptExtracted, void(const std::string atPrompt) );

};




TEST( CCircularATLineExtractor, BasicMockTest )
{
	ATLineConsumerMock atLineConsumerMock;

	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("exampleApp") )).Times(1);

	atLineConsumerMock.NotifyATResponseExtracted( std::string("exampleApp") );
}
