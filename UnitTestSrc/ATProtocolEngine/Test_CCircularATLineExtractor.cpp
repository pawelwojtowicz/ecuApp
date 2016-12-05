#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ATProtocolEngine/CCircularATLineExtractor.h>
#include <ATProtocolEngine/IATLineConsumer.h>

//using ::testing::AtLeast;
//using ::testing::Return;
using ::testing::EndsWith;
//using ::testing::NotNull;
//using ::testing::InSequence;
//using ::testing::_;


class ATLineConsumerMock : public ATProtocolEngine::IATLineConsumer
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

	ATProtocolEngine::CCircularATLineExtractor extractor(30,0);

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

TEST( CCircularATLineExtractor, BufferSizeCalculation_ATCommandsReceived )
{
	char test[] = {"\r\n12345\r\n67890"};

	ATProtocolEngine::CCircularATLineExtractor extractor(30,0);

	ASSERT_TRUE(extractor.WriteBuffer(test,5) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), 27);

	ASSERT_TRUE(extractor.WriteBuffer(test+5,8) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), 26);
}

TEST( CCircularATLineExtractor, BufferSizeCalculation_ATCommandsReceived_BufferOverrun )
{
	const size_t cyclicBufferSize(10);
	char test[] = {"\r\n12345\r\n6789019\r\n111"};

	ATProtocolEngine::CCircularATLineExtractor extractor(cyclicBufferSize,0);

	ASSERT_TRUE(extractor.WriteBuffer(test,5) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), cyclicBufferSize-3);

	ASSERT_TRUE(extractor.WriteBuffer(test+5,5) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), cyclicBufferSize-1);

	ASSERT_TRUE(extractor.WriteBuffer(test+10,6) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), cyclicBufferSize-7);

	ASSERT_TRUE(extractor.WriteBuffer(test+16,2) );
	ASSERT_EQ(extractor.GetRemainingSpaceSize(), cyclicBufferSize);
}

TEST( CCircularATLineExtractor, LineExtraction_Basic )
{
	char test[] = {"\r\nTest1\r\nKaka1\r\n12345678\r\nddddddd"};

	ATLineConsumerMock atLineConsumerMock;


	ATProtocolEngine::CCircularATLineExtractor extractor(100,&atLineConsumerMock);
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

TEST( CCircularATLineExtractor, LineExtraction_LongLine )
{
	char test[] = {"\r\nTest1\r\nKaka1\r\n12345678\r\nddddddd"};

	ATLineConsumerMock atLineConsumerMock;


	ATProtocolEngine::CCircularATLineExtractor extractor(11,&atLineConsumerMock);
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

TEST( CCircularATLineExtractor, LineExtraction_TerminationSequenceOnBorder )
{
	char test[] = {"\r\nTest1\r\nKaka1\r\n12345678\r\nddddddd"};

	ATLineConsumerMock atLineConsumerMock;


	ATProtocolEngine::CCircularATLineExtractor extractor(15,&atLineConsumerMock);
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

TEST( CCircularATLineExtractor, LineExtraction_TerminationSequenceRightBeforeBorder )
{
	char test[] = {"\r\nTest1\r\nKaka1\r\n12345678\r\nddddddd"};

	ATLineConsumerMock atLineConsumerMock;


	ATProtocolEngine::CCircularATLineExtractor extractor(16,&atLineConsumerMock);
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


TEST( CCircularATLineExtractor, PromptExtraction_LongLine )
{
	char test[] = {"\r\nTest1\r\n<Kaka1>\r\n12345678\r\nddddddd"};

	ATLineConsumerMock atLineConsumerMock;


	ATProtocolEngine::CCircularATLineExtractor extractor(16,&atLineConsumerMock);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("Test1") )).Times(1);
	EXPECT_CALL(atLineConsumerMock, NotifyATPromptExtracted(	EndsWith("Kaka1") )).Times(1);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("12345678") )).Times(1);

	ASSERT_TRUE(extractor.WriteBuffer(test,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+5,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+10,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+15,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+20,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+25,5));
}

TEST( CCircularATLineExtractor, PromptExtraction_IgnoreNotTerminated )
{
	char test[] = {"\r\nTest1\r\n<Kaka1\r\n12345678\r\nddddddd"};

	ATLineConsumerMock atLineConsumerMock;


	ATProtocolEngine::CCircularATLineExtractor extractor(16,&atLineConsumerMock);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("Test1") )).Times(1);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("<Kaka1") )).Times(1);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("12345678") )).Times(1);

	ASSERT_TRUE(extractor.WriteBuffer(test,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+5,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+10,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+15,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+20,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+25,5));
}

TEST( CCircularATLineExtractor, PromptExtraction_IgnoreNotStarted )
{
	char test[] = {"\r\nTest1\r\nKaka1>\r\n12345678\r\nddddddd"};

	ATLineConsumerMock atLineConsumerMock;


	ATProtocolEngine::CCircularATLineExtractor extractor(16,&atLineConsumerMock);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("Test1") )).Times(1);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("Kaka1>") )).Times(1);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("12345678") )).Times(1);

	ASSERT_TRUE(extractor.WriteBuffer(test,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+5,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+10,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+15,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+20,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+25,5));
}


TEST( CCircularATLineExtractor, PromptExtraction_IgnorePromptMarkupInTheMiddle )
{
	char test[] = {"\r\nTest1\r\nK<aka>1\r\n12345678\r\nddddddd"};

	ATLineConsumerMock atLineConsumerMock;


	ATProtocolEngine::CCircularATLineExtractor extractor(16,&atLineConsumerMock);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("Test1") )).Times(1);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("K<aka>1") )).Times(1);
	EXPECT_CALL(atLineConsumerMock, NotifyATResponseExtracted(	EndsWith("12345678") )).Times(1);

	ASSERT_TRUE(extractor.WriteBuffer(test,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+5,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+10,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+15,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+20,5));
	ASSERT_TRUE(extractor.WriteBuffer(test+25,5));
}

