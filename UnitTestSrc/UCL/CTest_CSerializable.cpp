#include <gtest/gtest.h>
#include "UCL/CSerializable.h"

class TestClass : public UCL::CSerializable
{
public:
	Int8 signedNumber8bit;
	UInt8 unsignedNumber8bit;
	
	Int16 signedNumber16bit;
	UInt16 unsignedNumber16bit;

	Int32 signedNumber32bit;
	UInt32 unsignedNumber32bit;
	
	std::string text;
	
private:
	virtual bool ToByteStream()
		{
			bool serializationStatus(false);
			
			serializationStatus = SetValue(signedNumber8bit);
			serializationStatus &= SetValue(unsignedNumber8bit);
			serializationStatus &= SetValue(signedNumber16bit);
			serializationStatus &= SetValue(unsignedNumber16bit);
			serializationStatus &= SetValue(signedNumber32bit);
			serializationStatus &= SetValue(unsignedNumber32bit);
			serializationStatus &= SetValue(text);
			
			return serializationStatus;
		};
		
	virtual bool FromByteStream()
		{
			bool deserializationStatus(false);

			deserializationStatus = GetValue(signedNumber8bit);
			deserializationStatus &= GetValue(unsignedNumber8bit);
			deserializationStatus &= GetValue(signedNumber16bit);
			deserializationStatus &= GetValue(unsignedNumber16bit);
			deserializationStatus &= GetValue(signedNumber32bit);
			deserializationStatus &= GetValue(unsignedNumber32bit);
			deserializationStatus &= GetValue(text);

			return deserializationStatus;	
		};

		virtual size_t GetStorageSize() { return 0;};

};

TEST(CSerializable,BasicSerializaDeserialize)
{
	size_t bufferSize(255);
	Int8 * pBuffer = new Int8[bufferSize];
	
	TestClass input;
	input.signedNumber8bit = 14;	
	input.unsignedNumber8bit = 16;	
	input.signedNumber16bit = 1025;	
	input.unsignedNumber16bit = 4096;	
	input.signedNumber32bit = 100123;	
	input.unsignedNumber32bit = 1234321;
	input.text = "This is simple test";	

	size_t outputSize = input.Serialize(pBuffer, bufferSize);

	TestClass output;
	
	ASSERT_TRUE(output.Deserialize(pBuffer, outputSize));
	
	EXPECT_EQ(input.signedNumber8bit , output.signedNumber8bit);	
	EXPECT_EQ(input.unsignedNumber8bit , output.unsignedNumber8bit);	
	EXPECT_EQ(input.signedNumber16bit , output.signedNumber16bit);	
	EXPECT_EQ(input.unsignedNumber16bit , output.unsignedNumber16bit);	
	EXPECT_EQ(input.signedNumber32bit , output.signedNumber32bit);	
	EXPECT_EQ(input.unsignedNumber32bit , output.unsignedNumber32bit);
	EXPECT_EQ(input.text, output.text);
	
	delete [] pBuffer;
}

TEST(CSerializable,Serialization_BufferTooSmall)
{
	size_t bufferSize(30);
	Int8 * pBuffer = new Int8[bufferSize];
	
	TestClass input;
	input.signedNumber8bit = 14;	
	input.unsignedNumber8bit = 16;	
	input.signedNumber16bit = 1025;	
	input.unsignedNumber16bit = 4096;	
	input.signedNumber32bit = 100123;	
	input.unsignedNumber32bit = 1234321;
	input.text = "This is simple test";	

	EXPECT_EQ( 0 , input.Serialize(pBuffer, bufferSize));
	
	delete [] pBuffer;
}


TEST(CSerializable,Deserialize_IncompleteBuffer)
{
	size_t bufferSize(255);
	Int8 * pBuffer = new Int8[bufferSize];
	
	TestClass input;
	input.signedNumber8bit = 14;	
	input.unsignedNumber8bit = 16;	
	input.signedNumber16bit = 1025;	
	input.unsignedNumber16bit = 4096;	
	input.signedNumber32bit = 100123;	
	input.unsignedNumber32bit = 1234321;
	input.text = "This is simple test";	

	size_t outputSize = input.Serialize(pBuffer, bufferSize);

	TestClass output;
	
	ASSERT_FALSE(output.Deserialize(pBuffer, outputSize-4));	
	delete [] pBuffer;
}

TEST(CSerializable, Serialize_ExactSizeMatching)
{
	size_t bufferSize(255);
	Int8 * pBuffer = new Int8[bufferSize];
	
	TestClass input;
	input.signedNumber8bit = 14;	
	input.unsignedNumber8bit = 16;	
	input.signedNumber16bit = 1025;	
	input.unsignedNumber16bit = 4096;	
	input.signedNumber32bit = 100123;	
	input.unsignedNumber32bit = 1234321;
	input.text = "This is simple test";	

	EXPECT_EQ (	(	sizeof(Int8)+
								sizeof(UInt8)+
								sizeof(Int16) + 
								sizeof(UInt16)+
								sizeof(Int32)+
								sizeof(UInt32) + 
								sizeof(UInt8)+ // the size of the string is rolled there.
								input.text.length()*sizeof(std::string::value_type)), input.Serialize(pBuffer, bufferSize) );
	
	delete [] pBuffer;
}

