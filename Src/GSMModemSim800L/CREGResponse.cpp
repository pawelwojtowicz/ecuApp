#include "CREGResponse.h"
#include <ATProtocolEngine/CParameterBundle.h>
#include <UCL/CTokenizer.h>

namespace GSMModemSim800L
{
const std::string CREGResponse::Deserialize( const std::string& input, ATProtocolEngine::CParameterBundle& bundle ) const
{
	// the data are comming in the following format:
	// +CREG: <n>,<stat>[,<lac>,<ci>]
	// n 		- registration modes 
	// stat - registrationStatus 
	// lac 	- location area code
	// ci		- cell id
	size_t responseParameterPosition(input.find_first_not_of("+CREG: "));

	if (std::string::npos != responseParameterPosition)
	{
		std::string parametersString(input, responseParameterPosition);
		UCL::CTokenizer parameters(parametersString, ",");

		if ( 1 < parameters.GetTokenCount() )
		{
			bundle.Store("REG_MODE", parameters.GetToken(0));
			bundle.Store("REG_STATE", parameters.GetToken(1));

			if ( 4 == parameters.GetTokenCount() )
			{
				bundle.Store("LAC", parameters.GetToken(2));
				bundle.Store("CI", parameters.GetToken(3));
			}

			return std::string("E_REG_STATE");
		}
	}
	return std::string();
}
}
