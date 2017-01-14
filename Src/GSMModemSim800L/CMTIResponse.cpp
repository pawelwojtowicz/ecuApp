#include "CMTIResponse.h"
#include <ATProtocolEngine/CParameterBundle.h>
#include <UCL/CTokenizer.h>
#include <algorithm>

namespace GSMModemSim800L
{
const std::string CMTIResponse::Deserialize( const std::string& input, ATProtocolEngine::CParameterBundle& bundle ) const
{
	// the data are comming in the following format:
	// +CMTTI: <mem>,<index>
	// mem 		- registration modes 
	// index - registrationStatus 
	size_t responseParameterPosition(input.find_first_not_of("+CMTI: "));

	if (std::string::npos != responseParameterPosition)
	{
		std::string parametersString(input, responseParameterPosition);
		parametersString.erase(std::remove(parametersString.begin(), parametersString.end(), '\"'), parametersString.end() );		
		UCL::CTokenizer parameters(parametersString, ",");

		if ( 2 == parameters.GetTokenCount() )
		{
			bundle.Store("MEMORY", parameters.GetToken(0));
			bundle.Store("INDEX", parameters.GetToken(1));

			return std::string("E_NEW_SMS_RECEIVED");
		}
	}
	return std::string();
}
}
