#include "CPINSerializer.h"
#include "ATProtocolEngine/CParameterBundle.h"

namespace GSMModemSim800L
{
bool CPINSerializer::Serialize( const ATProtocolEngine::CParameterBundle& bundle, std::string& msgText )
{
	if (bundle.IsAvailable("PIN") )
	{
		msgText = std::string("AT+CPIN=\"");
		msgText += bundle.GetParameter("PIN");
		msgText += std::string("\"");
		return true;
	}
	return false;
}

}
