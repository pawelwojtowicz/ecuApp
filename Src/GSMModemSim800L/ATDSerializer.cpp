#include "ATDSerializer.h"
#include "ATProtocolEngine/CParameterBundle.h"

namespace GSMModemSim800L
{
bool ATDSerializer::Serialize( const ATProtocolEngine::CParameterBundle& bundle, std::string& msgText )
{
	if (bundle.IsAvailable("NUMBER") )
	{
		msgText = std::string("ATD");
		msgText += bundle.GetParameter("NUMBER");
		msgText += std::string(";");
		return true;
	}
	return false;
}

}
