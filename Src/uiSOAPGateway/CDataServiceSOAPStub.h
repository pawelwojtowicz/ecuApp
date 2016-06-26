#ifndef UISOAPGATEWAY_CDATASERVICESOAPSTUB_H
#define UISOAPGATEWAY_CDATASERVICESOAPSTUB_H

#include "gSOAP_DataService/gSOAP_DS_DataServiceBindingService.h"

namespace uiSOAPGateway
{
class CDataServiceSOAPStub: public DataServiceBindingService
{
public:

	CDataServiceSOAPStub();
	virtual ~CDataServiceSOAPStub();

private:
	virtual DataServiceBindingService* copy();

	/// Web service operation 'GetServiceStatus' (returns error code or SOAP_OK)
	virtual	int GetServiceStatus(int &return_);

	/// Web service operation 'TrackData' (returns error code or SOAP_OK)
	virtual	int TrackData(std::string _trackItems, int &_return_);

	/// Web service operation 'ExecuteCommand' (returns error code or SOAP_OK)
	virtual	int ExecuteCommand(std::string _commandName, std::string _arguments, std::string &_return_);

	/// Web service operation 'GetData' (returns error code or SOAP_OK)
	virtual	int GetData(std::string _itemName, std::string &_return_);
};
}
#endif
