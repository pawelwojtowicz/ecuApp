#pragma once
#include "IATIncomingMessage.h"

namespace GSMModemSim800L
{
class CSQResponse: public IATIncomingMessage
{
private:
	virtual const std::string Deserialize( const std::string& input, ATProtocolEngine::CParameterBundle& bundle ) const;
};
}
