#include "CDataServiceSOAPStub.h"
#include "gSOAP_DataService/DataServiceBinding.nsmap"
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
	return this;
}


int CDataServiceSOAPStub::GetServiceStatus(int &return_)
{
	return SOAP_OK;
}

int CDataServiceSOAPStub::TrackData(std::string _trackItems, int &_return_)
{
	return SOAP_OK;
}

int CDataServiceSOAPStub::ExecuteCommand(std::string _commandName, std::string _arguments, std::string &_return_)
{
	return SOAP_OK;
}

int CDataServiceSOAPStub::GetData(std::string _itemName, std::string &_return_)
{
	return SOAP_OK;
}

}
