#include "CLIPResponse.h"
#include <ATProtocolEngine/CParameterBundle.h>
#include <UCL/CTokenizer.h>
#include <algorithm>

namespace GSMModemSim800L
{
const std::string CLIPResponse::Deserialize( const std::string& input, ATProtocolEngine::CParameterBundle& bundle ) const
{
	// the data are comming in the following format:
	// +CLIP: <number>,<type>[,<subaddr>,<satype>,<alphaID>,<CLIValidity>]
	// number 			- phone number of the incomming call 
	// type 				- type of the caller
	// subaddr 			- origin address/destination address - phone number, shortly speaking
	// satype 			- human readable representation of the number ( based on the phonebook )
	// alphaId			-	timestamp
	// CLIValidity	- 
	size_t responseParameterPosition(input.find_first_not_of("+CLIP: "));

	if (std::string::npos != responseParameterPosition)
	{
		std::string parametersString(input, responseParameterPosition);
		parametersString.erase(std::remove(parametersString.begin(), parametersString.end(), '\"'), parametersString.end() );
		UCL::CTokenizer parameters(parametersString, ",");
		size_t paramCount(parameters.GetTokenCount());

		if ( 1 < paramCount )
		{
			bundle.Store("NUMBER", parameters.GetToken(0));
			bundle.Store("TYPE", parameters.GetToken(1));
		
			if ( 2 < paramCount )
			{
				bundle.Store("SUBADDR", parameters.GetToken(2));
				bundle.Store("SATYPE", parameters.GetToken(3));
				bundle.Store("ALPHA_ID", parameters.GetToken(4));
				bundle.Store("CLI_VALIDITY", parameters.GetToken(5));
			}

			return std::string("E_CALLER_IDENTIFICATION");
		}
	}
	return std::string();
}
}
