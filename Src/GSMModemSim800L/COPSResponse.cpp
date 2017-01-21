#include "COPSResponse.h"
#include <ATProtocolEngine/CParameterBundle.h>
#include <UCL/CTokenizer.h>
#include <algorithm>
#include "GSMModemSim800LConst.h"

namespace GSMModemSim800L
{
const std::string COPSResponse::Deserialize( const std::string& input, ATProtocolEngine::CParameterBundle& bundle ) const
{
	// the data are comming in the following format:
	// +COPS: <stat>,<format>,<oper>
	// stat 			- status of the message 
	// format			- format of the operator name
	// oper				- operator name
	size_t responseParameterPosition(input.find_first_not_of("+COPS: "));

	if (std::string::npos != responseParameterPosition)
	{
		std::string parametersString(input, responseParameterPosition);
		parametersString.erase(std::remove(parametersString.begin(), parametersString.end(), '\"'), parametersString.end() );
		UCL::CTokenizer parameters(parametersString, ",");
		size_t paramCount(parameters.GetTokenCount());

		if ( 0 < paramCount )
		{
			bundle.Store( sc_COPS_operatorState, parameters.GetToken(0));
			if ( 1 < paramCount )
			{
				bundle.Store(	sc_COPS_operatorFormat, parameters.GetToken(1));
				bundle.Store( sc_COPS_operatorName, parameters.GetToken(2));
			}
			return std::string("E_OPERATOR_NAME");
		}
	}
	return std::string();
}
}
