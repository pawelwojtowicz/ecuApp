#include <gtest/gtest.h>
#include <JSONLib/json.h>

TEST( JSONLibraryTests,Basic )
{	
	json::Object newObject;
	
	newObject["Title"] = std::string("New test of the JSON library");
	
	
	json::Array testArray;
	json::Object arrayValue;

	arrayValue["x"] = 1;
	arrayValue["y"] = 1;	
	testArray.push_back(arrayValue);

	arrayValue["x"] = 2;
	arrayValue["y"] = 4;	
	testArray.push_back(arrayValue);

	arrayValue["x"] = 3;
	arrayValue["y"] = 9;	
	testArray.push_back(arrayValue);

	arrayValue["x"] = 4;
	arrayValue["y"] = 16;	
	testArray.push_back(arrayValue);

	arrayValue["x"] = 5;
	arrayValue["y"] = 25;	
	testArray.push_back(arrayValue);
	
	newObject["data"] = testArray;
	
	std::string serializedString = json::Serialize(newObject);
	
	printf("\n\n\n\n\n%s\n\n\n\n\n", serializedString.c_str());
	
	ASSERT_TRUE( !serializedString.empty() );
	
}

