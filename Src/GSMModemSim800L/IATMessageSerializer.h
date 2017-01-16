#pragma once
#include <Global/GlobalTypes.h>

namespace ATProtocolEngine
{
class CParameterBundle;
}

namespace GSMModemSim800L
{
class IATMessageSerializer
{
public:
	virtual ~IATMessageSerializer() {};
	virtual bool Serialize( const ATProtocolEngine::CParameterBundle& bundle, std::string& msgText ) = 0;

};
}
