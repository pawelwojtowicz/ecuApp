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


TEST( CCircularATLineExtractor, BufferSizeCalculation_Basic )
{
	char test[] = {"1234567890"};

	ZigBeeDaemon::CCircularATLineExtractor extractor(30,0);

	ASSERT_TRUE(extractor.WriteBuffer(test,5) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), 25);

	ASSERT_TRUE(extractor.WriteBuffer(test,7) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), 18);

	ASSERT_TRUE(extractor.WriteBuffer(test,8) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), 10);

	ASSERT_TRUE(extractor.WriteBuffer(test,5) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), 5);

	ASSERT_FALSE(extractor.WriteBuffer(test,8) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), 5);
}



TEST( CCircularATLineExtractor, BufferSizeCalculation_ATCommandsReceived_BufferOverrun )
{
	const size_t cyclicBufferSize(10);
	char test[] = {"\n\r12345\n\r6789019\n\r111"};

	ZigBeeDaemon::CCircularATLineExtractor extractor(cyclicBufferSize,0);

	ASSERT_TRUE(extractor.WriteBuffer(test,5) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), cyclicBufferSize-3);

	ASSERT_TRUE(extractor.WriteBuffer(test+5,5) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), cyclicBufferSize-1);

	ASSERT_TRUE(extractor.WriteBuffer(test+10,6) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), cyclicBufferSize-7);

	ASSERT_TRUE(extractor.WriteBuffer(test+16,2) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), cyclicBufferSize);
}

TEST( CCircularATLineExtractor, BufferSizeCalculation_ATCommandsReceived )
{
	char test[] = {"\n\r12345\n\r67890"};

	ZigBeeDaemon::CCircularATLineExtractor extractor(30,0);

	ASSERT_TRUE(extractor.WriteBuffer(test,5) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), 27);

	ASSERT_TRUE(extractor.WriteBuffer(test+5,8) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), 26);
}


TEST( CCircularATLineExtractor, LineExtraction_Basic )
{
	char test[] = {"\n\rTest1\n\rKaka1\n\r12345678\n\rddddddd"};

	ATLineConsumerMock atLineConsumerMock;


	ZigBeeDaemon::CCircularATLineExtractor extractor(100,&atLineConsumerMock);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("Test1") )).Times(1);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("Kaka1") )).Times(1);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("12345678") )).Times(1);

	extractor.WriteBuffer(test,5);
	extractor.WriteBuffer(test+5,5);
	extractor.WriteBuffer(test+10,5);
	extractor.WriteBuffer(test+15,5);
	extractor.WriteBuffer(test+20,5);
	extractor.WriteBuffer(test+25,5);
}

TEST( CCircularATLineExtractor, LineExtraction_BufferOverrun )
{
	char test[] = {"\n\rTest1\n\rKaka1\n\r12345678\n\rddddddd"};

	ATLineConsumerMock atLineConsumerMock;


	ZigBeeDaemon::CCircularATLineExtractor extractor(11,&atLineConsumerMock);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("Test1") )).Times(1);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("Kaka1") )).Times(1);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("12345678") )).Times(1);

	ASSERT_TRUE(extractor.WriteBuffer(test,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+5,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+10,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+15,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+20,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+25,2));
}

TEST( CCircularATLineExtractor, LineExtraction_BufferOverrun_TerminationSequenceOnBorder )
{
	char test[] = {"\n\rTest1\n\rKaka1\n\r12345678\n\rddddddd"};

	ATLineConsumerMock atLineConsumerMock;


	ZigBeeDaemon::CCircularATLineExtractor extractor(15,&atLineConsumerMock);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("Test1") )).Times(1);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("Kaka1") )).Times(1);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("12345678") )).Times(1);

	ASSERT_TRUE(extractor.WriteBuffer(test,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+5,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+10,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+15,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+20,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+25,2));
}

TEST( CCircularATLineExtractor, LineExtraction_BufferOverrun_TerminationSequenceRightBeforeBorder )
{
	char test[] = {"\n\rTest1\n\rKaka1\n\r12345678\n\rddddddd"};

	ATLineConsumerMock atLineConsumerMock;


	ZigBeeDaemon::CCircularATLineExtractor extractor(16,&atLineConsumerMock);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("Test1") )).Times(1);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("Kaka1") )).Times(1);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("12345678") )).Times(1);

	ASSERT_TRUE(extractor.WriteBuffer(test,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+5,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+10,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+15,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+20,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+25,2));
}

