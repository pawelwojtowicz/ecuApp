#pragma once
#include <Global/GlobalTypes.h>
#include <queue>

namespace GSMModemSim800L
{
class CSMSOutbox
{
public:
	struct tSMS
	{
	std::string TrgtNumber;
	std::string MessageText;
	UInt32 MessageId;
	};
private:
	typedef std::queue<tSMS> tSMSQueue;

public:
	CSMSOutbox();
	virtual ~CSMSOutbox();

	UInt32 EnqueueSMS( const std::string& targetNubmer, const std::string& msgText );

	bool QueueNotEmpty();

	bool GetNextMessage( tSMS& msg );
	
	void ConfirmMsgSent( const UInt32 msgId );

private:
	CSMSOutbox(const CSMSOutbox&);
	CSMSOutbox& operator=(const CSMSOutbox&);

	UInt32 m_currentOrderId;

	tSMSQueue m_messageQueue;
};
}
