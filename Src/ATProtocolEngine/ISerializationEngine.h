#pragma once
#include <Global/GlobalTypes.h>

namespace ATProtocolEngine
{
class CParameterBundle;

class ISerializationEngine
{
public:
	ISerializationEngine() {};
	virtual ~ISerializationEngine() {};

	virtual bool SerializeMsg( const std::string& msdId, const CParameterBundle& bundle, std::string& msgText ) = 0; 

	virtual const std::string Deserialize( const std::string& inputData, CParameterBundle& bundle) = 0;

private:
	ISerializationEngine(const ISerializationEngine&);
	ISerializationEngine& operator=(const ISerializationEngine&);
};
}
