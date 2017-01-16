#include "CREGSerializer.h"
#include "ATProtocolEngine/CParameterBundle.h"

namespace GSMModemSim800L
{
bool CREGSerializer::Serialize( const ATProtocolEngine::CParameterBundle& bundle, std::string& msgText )
{
	if (bundle.IsAvailable("PIN") )
	{
		msgText = std::string("AT+CREG=\"");
		msgText += bundle.GetParameter("PIN");
		msgText += std::string("\"");
		return true;
	}
	return false;
}

}
