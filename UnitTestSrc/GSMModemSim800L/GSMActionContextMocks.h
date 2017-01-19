#pragma once
#include <GSMDaemon/ISMSServiceListener.h>
using ::testing::Return;
using ::testing::EndsWith;


class SMSServiceListenerMock: public GSMDaemon::ISMSServiceListener
{
public:

	MOCK_METHOD0( NotifySMSSendSuccess, void() );
	MOCK_METHOD0( NotifySMSSendFailure, void() );
	MOCK_METHOD3( NotifyIncomingSMS, void ( const std::string& srcNumber, const std::string& timestamp, const std::string& messageText) );
};
