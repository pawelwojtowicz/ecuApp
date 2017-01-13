#include "COKResponse.h"
#include <ATProtocolEngine/CParameterBundle.h>

namespace GSMModemSim800L
{
const std::string COKResponse::Deserialize( const std::string& input, ATProtocolEngine::CParameterBundle& bundle ) const
{
	return std::string("E_OK");
}
}
