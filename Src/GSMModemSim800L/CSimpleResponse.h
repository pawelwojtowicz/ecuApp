#pragma once
#include "IATIncomingMessage.h"

namespace GSMModemSim800L
{
class CSimpleResponse: public IATIncomingMessage
{
public:
	CSimpleResponse( const std::string& eventName);
private:
	virtual const std::string Deserialize( const std::string& input, ATProtocolEngine::CParameterBundle& bundle ) const;

private:
	std::string m_eventName;
};
}
