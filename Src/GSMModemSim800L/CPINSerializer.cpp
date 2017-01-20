#include "CPINSerializer.h"
#include "ATProtocolEngine/CParameterBundle.h"
#include "GSMModemSim800LConst.h"

namespace GSMModemSim800L
{
bool CPINSerializer::Serialize( const ATProtocolEngine::CParameterBundle& bundle, std::string& msgText )
{
	if (bundle.IsAvailable(GSMModemSim800L::sc_CPIN_pin) )
	{
		msgText = std::string("AT+CPIN=\"");
		msgText += bundle.GetParameter(GSMModemSim800L::sc_CPIN_pin);
		msgText += std::string("\"");
		return true;
	}
	return false;
}

}
