#include "CPINResponse.h"
#include <ATProtocolEngine/CParameterBundle.h>

namespace GSMModemSim800L
{
const std::string CPINResponse::Deserialize( const std::string& input, ATProtocolEngine::CParameterBundle& bundle ) const
{
	// the data are comming in the following format:
	// +CPIN: SIM PIN
	// +CPIN: SIM PUK
	// +CPIN: READY
	size_t statusPosition(input.find_first_not_of("+CPIN: "));

	if (std::string::npos != statusPosition)
	{
		std::string pinStatus(input, statusPosition);

		bundle.Store("SIMSTATUS", pinStatus);
		return std::string("E_SIM_STATUS");
	}
	return std::string();
}
}
