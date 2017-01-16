#include "CMGSSerializer.h"
#include "ATProtocolEngine/CParameterBundle.h"

namespace GSMModemSim800L
{
bool CMGSSerializer::Serialize( const ATProtocolEngine::CParameterBundle& bundle, std::string& msgText )
{
	if (bundle.IsAvailable("NUMBER") && bundle.IsAvailable("TEXT") )
	{
		msgText = std::string("AT+CMGS=\"");
		msgText += bundle.GetParameter("NUMBER");
		msgText += std::string("\"\r");
		msgText += bundle.GetParameter("TEXT");
		msgText += std::string("\x1A");
		return true;
	}
	return false;
}

}
