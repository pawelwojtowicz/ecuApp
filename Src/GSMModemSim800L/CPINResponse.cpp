#include "CPINResponse.h"
#include <ATProtocolEngine/CParameterBundle.h>

namespace GSMModemSim800L
{
const std::string CPINResponse::Deserialize( const std::string& input, ATProtocolEngine::CParameterBundle& bundle ) const
{
	return std::string("E_PIN_STATUS");
}
}
