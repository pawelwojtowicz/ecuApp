#pragma once
#include "Global/GlobalTypes.h"


namespace GSMModemSim800L
{
class CPDUMessage
{
public:
	CPDUMessage();
	virtual ~CPDUMessage();

	bool Deserialize( const std::string& incommingMessage);
	bool IsValid() const;

	const std::string& GetServiceCenterNumber() const;
	const std::string& GetSenderNumber() const;

private:
	UInt8 ExtractHexDigit( const char character );

private:
	CPDUMessage(const CPDUMessage&);
	CPDUMessage& operator=(const CPDUMessage&);

	bool m_valid;

	UInt8 m_smscAddressType;
	std::string m_serviceCenter;
	std::string m_senderNumber;
	UInt8 			m_TP_PID;
	UInt8				m_TP_DCS;
	std::string m_timestamp;
	std::string m_messageText;
};
}
