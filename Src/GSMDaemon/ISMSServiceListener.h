#pragma once

namespace GSMDaemon
{
class ISMSServiceListener
{
public:
	ISMSServiceListener() {};
	virtual ~ISMSServiceListener() {};

	virtual void NotifySMSSendSuccess( const UInt32 msgId ) = 0;
	virtual void NotifySMSSendFailure( const UInt32 msgId ) = 0;

	virtual void NotifyIncomingSMS( const std::string& srcNumber, const std::string& timestamp, const std::string& messageText) = 0;

private:
	ISMSServiceListener( const ISMSServiceListener&);
	ISMSServiceListener& operator=(const ISMSServiceListener&);
};
}
