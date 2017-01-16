#pragma once
#include "IATMessageSerializer.h"

namespace GSMModemSim800L
{
class CMGSSerializer : public IATMessageSerializer
{
	/** serializes the AT+CMGS AT command
			- sending an SMS
			- requires to parameters in the bundle NUMBER, and TEXT 
	*/
private:
		virtual bool Serialize( const ATProtocolEngine::CParameterBundle& bundle, std::string& msgText ); 
};
}
