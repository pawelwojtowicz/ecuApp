#include "CDataServiceSOAPStub.h"
#include "gSOAP_DataService/DataServiceBinding.nsmap"
#include <stdio.h>
namespace uiSOAPGateway 
{

CDataServiceSOAPStub::CDataServiceSOAPStub()
{
}

CDataServiceSOAPStub::~CDataServiceSOAPStub()
{
}

DataServiceBindingService* CDataServiceSOAPStub::copy()
{
	printf("teraz kopia\n");
	DataServiceBindingService *dup = SOAP_NEW_COPY(DataServiceBindingService(*(struct soap*)this));
	return dup;
}


int CDataServiceSOAPStub::GetServiceStatus(int &return_)
{
	
	printf("GetServiceStatus() from %s\n", inet_ntoa(peer.sin_addr));
	return_ = 101;
	return SOAP_OK;
}

int CDataServiceSOAPStub::TrackData(std::string _trackItems, int &_return_)
{
	printf("TrackData(%s)\n", _trackItems.c_str() );
	return SOAP_OK;
}

int CDataServiceSOAPStub::ExecuteCommand(std::string _commandName, std::string _arguments, std::string &_return_)
{
	printf("ExecuteCommand(%s)\n", _commandName.c_str());
	return SOAP_OK;
}

int CDataServiceSOAPStub::GetData(std::string _itemName, std::string &_return_)
{
	printf("GetData(%s)\n",_itemName.c_str());
	return SOAP_OK;
}

}
