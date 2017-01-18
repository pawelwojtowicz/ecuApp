#include "CErrorResponse.h"
#include <ATProtocolEngine/CParameterBundle.h>

namespace GSMModemSim800L
{
const std::string CErrorResponse::Deserialize( const std::string& input, ATProtocolEngine::CParameterBundle& bundle ) const
{
	// the data are comming in the following format:
	// +CME ERROR: <errorCode>
	size_t errorCodePosition(input.find_first_not_of("+CME ERROR: "));

	if (std::string::npos != errorCodePosition)
	{
		std::string errorCode(input, errorCodePosition);

		bundle.Store("ERROR_CODE", errorCode);
		return std::string("E_ERROR");
	}
	return std::string();
}
}