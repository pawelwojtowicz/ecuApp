#include "CSimpleResponse.h"
#include <ATProtocolEngine/CParameterBundle.h>

namespace GSMModemSim800L
{
CSimpleResponse::CSimpleResponse( const std::string& eventName)
: m_eventName(eventName)
{
}


const std::string CSimpleResponse::Deserialize( const std::string& input, ATProtocolEngine::CParameterBundle& bundle ) const
{
	return m_eventName;
}
}
