#include <gtest/gtest.h>
#include <gmock/gmock.h>  // Brings in Google Mock.
#include <Runtime/CSharedStorage.h>


TEST( CSharedStorage, Initialization )
{
	bool initOK(false);
	
	Runtime::CSharedStorage storage("tmpFileName", 100, true);
	
	initOK = storage.Initialize();

	ASSERT_TRUE( initOK );
}
