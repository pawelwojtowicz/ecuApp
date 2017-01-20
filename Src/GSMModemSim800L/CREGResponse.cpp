#include "CREGResponse.h"
#include <ATProtocolEngine/CParameterBundle.h>
#include <UCL/CTokenizer.h>
#include "GSMModemSim800LConst.h"

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
			bundle.Store(sc_CREG_regMode, parameters.GetToken(0));
			bundle.Store(sc_CREG_regStatus, parameters.GetToken(1));

			if ( 4 == parameters.GetTokenCount() )
			{
				bundle.Store(sc_CREG_lac, parameters.GetToken(2));
				bundle.Store(sc_CREG_ci, parameters.GetToken(3));
			}

			return std::string("E_REG_STATE");
		}
	}
	return std::string();
}
}
