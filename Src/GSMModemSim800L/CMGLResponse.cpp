#include "CMGLResponse.h"
#include <ATProtocolEngine/CParameterBundle.h>
#include <UCL/CTokenizer.h>
#include <algorithm>
#include "GSMModemSim800LConst.h"

namespace GSMModemSim800L
{
const std::string CMGLResponse::Deserialize( const std::string& input, ATProtocolEngine::CParameterBundle& bundle ) const
{
	// the data are comming in the following format:
	// +CMGL: <index>,<stat>,<oa/da>[,<alpha>][,<scts>[,<tooa/toda>][,<length>]
	// index 			- index of the message in the storage 
	// stat 			- status of the message 
	// oa/da 			- origin address/destination address - phone number, shortly speaking
	// alpha 			- human readable representation of the number ( based on the phonebook )
	// scts				-	timestamp
	// tooa/toda	- 
	// length			- 
	size_t responseParameterPosition(input.find_first_not_of("+CMGL: "));

	if (std::string::npos != responseParameterPosition)
	{
		std::string parametersString(input, responseParameterPosition);
		parametersString.erase(std::remove(parametersString.begin(), parametersString.end(), '\"'), parametersString.end() );
		UCL::CTokenizer parameters(parametersString, ",");
		size_t paramCount(parameters.GetTokenCount());

		if ( 2 < paramCount )
		{
			bundle.Store( sc_CMGL_msgId, parameters.GetToken(0));
			bundle.Store(	sc_CMGL_msgState, parameters.GetToken(1));
			bundle.Store( sc_CMGL_msgOrgNo, parameters.GetToken(2));

			if ( 3 < paramCount )
			{
				bundle.Store(sc_CMGL_msgOrgNoTxt, parameters.GetToken(3));
			}

			if ( 4 < paramCount )
			{
				bundle.Store(sc_CMGL_msgTimeStamp, parameters.GetToken(4));
			}

			return std::string("E_SMS_DETAILS");
		}
	}
	return std::string();
}
}
