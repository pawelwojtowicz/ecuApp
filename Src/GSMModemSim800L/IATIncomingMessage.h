#pragma once
#include <Global/GlobalTypes.h>


namespace ATProtocolEngine
{
class CParameterBundle;
}

namespace GSMModemSim800L
{
class IATIncomingMessage
{
public:
	IATIncomingMessage() {};
	virtual ~IATIncomingMessage() {};

	virtual const std::string Deserialize( const std::string& input, ATProtocolEngine::CParameterBundle& bundle ) const = 0;
private:
	IATIncomingMessage(const IATIncomingMessage&);
	IATIncomingMessage& operator=(const IATIncomingMessage&);
};
}
