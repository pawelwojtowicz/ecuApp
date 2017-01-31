#include "DTMFResponse.h"
#include <ATProtocolEngine/CParameterBundle.h>
#include <UCL/CTokenizer.h>
#include "GSMModemSim800LConst.h"
#include <algorithm>

namespace GSMModemSim800L
{
const std::string DTMFResponse::Deserialize( const std::string& input, ATProtocolEngine::CParameterBundle& bundle ) const
{
	// the data are comming in the following format:
	// +DTMF: <KEY> 

	size_t responseParameterPosition(input.find_first_not_of("+DTMF: "));

	if (std::string::npos != responseParameterPosition)
	{
		std::string parameterString(input, responseParameterPosition);

		if (1 == parameterString.length() )
		{
			bundle.Store( sc_DTMF_code, parameterString);
			return std::string("E_DTMF_CODE_DETECTED");
		}
	}
	return std::string();
}
}
