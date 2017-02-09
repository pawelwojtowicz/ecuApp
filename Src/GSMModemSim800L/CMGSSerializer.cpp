#include "CMGSSerializer.h"
#include "ATProtocolEngine/CParameterBundle.h"
#include "GSMModemSim800LConst.h"

namespace GSMModemSim800L
{
bool CMGSSerializer::Serialize( const ATProtocolEngine::CParameterBundle& bundle, std::string& msgText )
{
	if (bundle.IsAvailable(sc_CMGS_trgtNumber) && bundle.IsAvailable(sc_CMGS_msgText) )
	{
		msgText = std::string("AT+CMGS=\"");
		msgText += bundle.GetParameter(sc_CMGS_trgtNumber);
		msgText += std::string("\"");
		return true;
	}
	return false;
}

}
