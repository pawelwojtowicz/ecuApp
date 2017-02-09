#include "CSMSOutbox.h"

namespace GSMModemSim800L
{

CSMSOutbox::CSMSOutbox()
: m_currentOrderId(0)
{
}

CSMSOutbox::~CSMSOutbox()
{
}

UInt32 CSMSOutbox::EnqueueSMS( const std::string& targetNumber, const std::string& msgText )
{
	// increase the job ID.
	++m_currentOrderId;

	tSMS newMessage;
	newMessage.TrgtNumber = targetNumber;
	newMessage.MessageText= msgText;
	newMessage.MessageId = m_currentOrderId;
	m_messageQueue.push(newMessage);

	return m_currentOrderId; 
}

bool CSMSOutbox::QueueNotEmpty()
{
	return !m_messageQueue.empty();
}

bool CSMSOutbox::GetNextMessage( tSMS& msg )
{
	if (!m_messageQueue.empty())
	{
		msg = m_messageQueue.front();
		return true;
	}
	return false;
}

void CSMSOutbox::ConfirmMsgSent( const UInt32 msgId )
{
	if ( !m_messageQueue.empty() )
	{
		if ( m_messageQueue.front().MessageId == msgId )
		{
			m_messageQueue.pop();
		}
	}
}

}
