#pragma once
#include "IATMessageSerializer.h"

namespace GSMModemSim800L
{
class ATDSerializer : public IATMessageSerializer
{
	/** serializes the ATD AT command
			- triggers the GSM call to the given number
			- requires 1 parameter in the bundle: NUMBER 
	*/
private:
		virtual bool Serialize( const ATProtocolEngine::CParameterBundle& bundle, std::string& msgText ); 
};
}
