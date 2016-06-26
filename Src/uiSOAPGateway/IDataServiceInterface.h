#ifndef UISOAPGATEWAY_IDATASERVICEINTERFACE_H
#define UISOAPGATEWAY_IDATASERVICEINTERFACE_H
#include <Global/GlobalTypes.h>

namespace uiSOAPGateway
{
class IDataServiceInterface
{
public:
	IDataServiceInterface() {};
	virtual ~IDataServiceInterface() {};

	Int32 GetServiceStatus( const std::string& ipAddress) = 0;
	Int32 TrackData( const std::string& ipAddpress, const tStringVector& trackedItemIds ) = 0;
	bool ExecuteCommand( const std::string& commandName, const tStringVector& arguments) = 0;
	bool GetData( const std::string& itemName, std::string& outputValue) = 0;

private:
	IDataServiceInterface& operator=(const IDataServiceInterface&);
	IDataServiceInterface(const IDataServiceInterface&);
};
}
#endif
