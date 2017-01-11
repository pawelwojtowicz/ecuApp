#include "CSim800LSerialization.h"
#include <ATProtocolEngine/CParameterBundle.h>


namespace GSMModemSim800L
{

CSim800LSerialization::CSim800LSerialization()
{
}

CSim800LSerialization::~CSim800LSerialization()
{
}

bool CSim800LSerialization::Initialize()
{
	return true;
}

void CSim800LSerialization::Shutdown()
{
}

bool CSim800LSerialization::SerializeMsg( const std::string& msdId, const ATProtocolEngine::CParameterBundle& bundle, std::string& msgText )
{
	return true;
}

const std::string CSim800LSerialization::Deserialize( const std::string& inputData, ATProtocolEngine::CParameterBundle& bundle)
{
	return std::string("temp");
}

}
