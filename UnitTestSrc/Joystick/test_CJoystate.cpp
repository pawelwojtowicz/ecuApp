#include <gtest/gtest.h>
#include <JoystickInterface/CJoyState.h>

TEST( CJoyState,Basic )
{	
	Joystick::CJoyState a;
	a.SetAxisCount(2);
	a.SetButtonCount(3);
	a.SetCrossCount(4);
	
	a.SetAxis(0,1);
	a.SetAxis(1,2);
	
	a.SetButtonState(0,1);
	a.SetButtonState(1,1);
	a.SetButtonState(2,0);
	
	a.SetCrossState(0,2);
	a.SetCrossState(1,3);
	a.SetCrossState(2,4);
	a.SetCrossState(3,5);
	
	size_t size(a.GetStorageSize());
	
	Int8* buffer = new Int8[size+10];
	
	size_t serializedSize = a.Serialize(buffer,size+10);
	
	EXPECT_EQ( serializedSize , size );

	
	Joystick::CJoyState b;
	
	ASSERT_TRUE(b.Deserialize(buffer,serializedSize));
	
	
	EXPECT_EQ( a.GetAxis( 0 ) , b.GetAxis( 0 ) );
	EXPECT_EQ( a.GetAxis( 1 ) , b.GetAxis( 1 ) );

	EXPECT_EQ( a.GetButtonState( 0 ) , b.GetButtonState( 0 ) );
	EXPECT_EQ( a.GetButtonState( 1 ) , b.GetButtonState( 1 ) );
	EXPECT_EQ( a.GetButtonState( 2 ) , b.GetButtonState( 2 ) );

	EXPECT_EQ( a.GetCrossState( 0 ) , b.GetCrossState( 0 ) );
	EXPECT_EQ( a.GetCrossState( 1 ) , b.GetCrossState( 1 ) );
	EXPECT_EQ( a.GetCrossState( 2 ) , b.GetCrossState( 2 ) );
	EXPECT_EQ( a.GetCrossState( 3 ) , b.GetCrossState( 3 ) );
	
}
