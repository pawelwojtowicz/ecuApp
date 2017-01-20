#include "ATDSerializer.h"
#include "ATProtocolEngine/CParameterBundle.h"
#include "GSMModemSim800LConst.h"

namespace GSMModemSim800L
{
bool ATDSerializer::Serialize( const ATProtocolEngine::CParameterBundle& bundle, std::string& msgText )
{
	if (bundle.IsAvailable(sc_ATD_trgtNumber) )
	{
		msgText = std::string("ATD");
		msgText += bundle.GetParameter(sc_ATD_trgtNumber);
		msgText += std::string(";");
		return true;
	}
	return false;
}

}
