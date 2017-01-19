#pragma once

namespace GSMDaemon
{
class ISMSServiceListener
{
public:
	ISMSServiceListener() {};
	virtual ~ISMSServiceListener() {};

	virtual void NotifySMSSendSuccess() = 0;
	virtual void NotifySMSSendFailure() = 0;

	virtual void NotifyIncomingSMS( const std::string& srcNumber, const std::string& timestamp, const std::string& messageText) = 0;

private:
	ISMSServiceListener( const ISMSServiceListener&);
	ISMSServiceListener& operator=(const ISMSServiceListener&);
};
}
