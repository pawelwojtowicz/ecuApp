#pragma once
#include "IATMessageSerializer.h"

namespace GSMModemSim800L
{
class CPINSerializer : public IATMessageSerializer
{
	/** serializes the AT+CPIN command which inputs the PIN of the simcard
			- requires 1 parameter in the bundle: PIN 
	*/
private:
		virtual bool Serialize( const ATProtocolEngine::CParameterBundle& bundle, std::string& msgText ); 
};
}
