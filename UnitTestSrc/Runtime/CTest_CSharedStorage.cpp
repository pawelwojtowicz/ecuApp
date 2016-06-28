#include <gtest/gtest.h>
#include <gmock/gmock.h>  // Brings in Google Mock.
#include <Runtime/CSharedStorage.h>


TEST( CSharedStorage, Initialization )
{
	bool initOK(false);
	
	Runtime::CSharedStorage storage;
	
	initOK = storage.Initialize("tmpFileName", 250, true);

	ASSERT_TRUE( initOK );

	storage.Shutdown();
}
