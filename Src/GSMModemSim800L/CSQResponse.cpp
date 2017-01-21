#include "CSQResponse.h"
#include <ATProtocolEngine/CParameterBundle.h>
#include <UCL/CTokenizer.h>
#include "GSMModemSim800LConst.h"

namespace GSMModemSim800L
{
const std::string CSQResponse::Deserialize( const std::string& input, ATProtocolEngine::CParameterBundle& bundle ) const
{
	// the data are comming in the following format:
	// +CSQ: <rssi>,<ber>
	// rssi - signal strength indication
	// ber 	- bit error rate in % 
	size_t signalStrengthDataPosition(input.find_first_not_of("+CSQ: "));

	if (std::string::npos != signalStrengthDataPosition)
	{
		std::string signalStrengthData(input, signalStrengthDataPosition);
		UCL::CTokenizer signalStrengthTokens(signalStrengthData,",");
		if ( 2 == signalStrengthTokens.GetTokenCount() )
		{
			bundle.Store(sc_CSQ_rssi, signalStrengthTokens.GetToken(0));
			bundle.Store(sc_CSQ_ber, signalStrengthTokens.GetToken(1));
		}

		return std::string("E_SIG_STRENGTH");
	}
	return std::string();
}
}
