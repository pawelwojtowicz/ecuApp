#pragma once
#include <ATProtocolEngine/ISerializationEngine.h>

namespace GSMModemSim800L
{
class IATIncomingMessage;

class CSim800LSerialization : public ATProtocolEngine::ISerializationEngine
{
	typedef std::map<std::string, IATIncomingMessage*> tMsgDeserializers;
public:
	CSim800LSerialization();
	virtual ~CSim800LSerialization();

	bool Initialize();
	void Shutdown();

private:
	/** implementation of ATProtocolEngine::ISerializationEngine */
	virtual bool SerializeMsg( const std::string& msdId, const ATProtocolEngine::CParameterBundle& bundle, std::string& msgText ); 
	virtual const std::string Deserialize( const std::string& inputData, ATProtocolEngine::CParameterBundle& bundle);


private:
	tMsgDeserializers m_deserializers;

};
}
