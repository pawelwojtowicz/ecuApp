#include <gtest/gtest.h>
#include <gmock/gmock.h>  // Brings in Google Mock.
#include <Runtime/CMessenger.h>
#include <Runtime/CMessage.h>
#include <Runtime/ISubscriber.h>
std::string ownQueueName("ownQueue");
std::string receiverQueueName("receiverQueue");
std::string testQueue1name("TestQueue1");
std::string testQueue2name("TestQueue2");
std::string testQueue3name("TestQueue3");
std::string testQueue4name("TestQueue4");

TEST( CMessenger,ConnectQeue_Basic )
{
	Runtime::CMessenger messenger;
	
	messenger.Initialize(ownQueueName);
	
	Int32 testQueue1Id(0);
	Int32 testQueue2Id(0);
	Int32 testQueue3Id(0);
	Int32 testQueue4Id(0);
	
	testQueue1Id = messenger.ConnectQueue(testQueue1name);
	testQueue2Id = messenger.ConnectQueue(testQueue2name);
	testQueue3Id = messenger.ConnectQueue(testQueue3name);
	testQueue4Id = messenger.ConnectQueue(testQueue4name);


  EXPECT_NE( testQueue1Id, 1 );
	EXPECT_NE( testQueue2Id, 1 );
  EXPECT_NE( testQueue3Id, 1 );
  EXPECT_NE( testQueue4Id, 1 );
  EXPECT_EQ( testQueue1Id, messenger.ConnectQueue(testQueue1name) );
	EXPECT_EQ( testQueue2Id, messenger.ConnectQueue(testQueue2name) );
  EXPECT_EQ( testQueue3Id, messenger.ConnectQueue(testQueue3name) );
  EXPECT_EQ( testQueue4Id, messenger.ConnectQueue(testQueue4name) );

	messenger.Shutdown();

}

TEST( CMessenger,ConnectQeue_OwnQueue )
{
	Runtime::CMessenger messenger;
	messenger.Initialize(ownQueueName);
	
	messenger.ConnectQueue(testQueue1name);
	messenger.ConnectQueue(testQueue2name);
	messenger.ConnectQueue(testQueue3name);
	messenger.ConnectQueue(testQueue4name);


  EXPECT_EQ( 1, messenger.ConnectQueue(ownQueueName) );
  
	messenger.Shutdown();

}

TEST( CMessenger,ConnectQeue_RefCount )
{
	Runtime::CMessenger messenger;
	messenger.Initialize(ownQueueName);
	
	Int32 q1firstPassId = messenger.ConnectQueue(testQueue1name);
	messenger.ConnectQueue(testQueue2name);
	messenger.ConnectQueue(testQueue3name);
	messenger.ConnectQueue(testQueue4name);
	Int32 q1secondPassId = messenger.ConnectQueue(testQueue1name);

	messenger.DisconnectQueue(testQueue1name);
	Int32 q1thirdPassId = messenger.ConnectQueue(testQueue1name);

	messenger.DisconnectQueue(testQueue1name);
	messenger.DisconnectQueue(testQueue1name);

	Int32 q1fourthPassId = messenger.ConnectQueue(testQueue1name);
	Int32 q1fifthPassId = messenger.ConnectQueue(testQueue1name);

  EXPECT_EQ( q1firstPassId , q1secondPassId );
  EXPECT_EQ( q1firstPassId , q1thirdPassId );
  EXPECT_NE( q1thirdPassId , q1fourthPassId );
 	EXPECT_EQ( q1fourthPassId,q1fifthPassId );
  
	messenger.Shutdown();
}


 
 using ::testing::AtLeast;
 using ::testing::Return;
 
 class CMokowana
 {
 public
 :
     virtual int PierwszaMetoda() = 0;
     virtual float DrugaMetoda( int tmp ) = 0;
     virtual float TrzeciaMetodaConst( int tmp ) const = 0;
 
 };
 
 class MockMokowanej: public CMokowana
 {
 public:
     MOCK_METHOD0(PierwszaMetoda, int() );
     MOCK_METHOD1(DrugaMetoda,float( int tmp ) );
     MOCK_CONST_METHOD1(TrzeciaMetodaConst,float( int tmp ) );
 };
 
 
 class Testowana
 {
 public:
     Testowana( CMokowana& referencja ):m_ref(referencja) {}
 
     int Metoda1()
     {
         return m_ref.PierwszaMetoda();
     }
 
     float Metoda2( int tmp )
     {
         return m_ref.DrugaMetoda(tmp);
     }
 
     float Metoda3( int tmp )
     {
         return m_ref.TrzeciaMetodaConst( tmp );
     }
 
 private:
     CMokowana& m_ref;
 };
 
 TEST(PainterTest, CanDrawSomething)
 {
   MockMokowanej mok;                          // #2
   EXPECT_CALL(mok, PierwszaMetoda())              // #3
       .Times(3).WillOnce(Return(0)).WillRepeatedly(Return(1));
 
   Testowana tmp(mok);// #4
   EXPECT_FALSE(tmp.Metoda1());
   EXPECT_TRUE(tmp.Metoda1());
 
   EXPECT_TRUE( tmp.Metoda1() );
 }
 
 TEST(PainterTest, Argumentowana)
 {
   MockMokowanej mok;                          // #2
   EXPECT_CALL(mok, DrugaMetoda(123))              // #3
       .Times(1).WillOnce(Return(13));
 
   Testowana tmp(mok);// #4
 
   ASSERT_FLOAT_EQ(13,tmp.Metoda2(123));
 }
 
 
 

