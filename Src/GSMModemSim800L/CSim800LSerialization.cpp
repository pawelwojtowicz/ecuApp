#include "CSim800LSerialization.h"
#include <ATProtocolEngine/CParameterBundle.h>
#include <UCL/CTokenizer.h>
#include "IATIncomingMessage.h"
#include "COKResponse.h"


namespace GSMModemSim800L
{

CSim800LSerialization::CSim800LSerialization()
{
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("OK"), new COKResponse() ) );
}

CSim800LSerialization::~CSim800LSerialization()
{
	for(tMsgDeserializers::iterator iter = m_deserializers.begin() ; m_deserializers.end() != iter ; ++iter )
	{
		delete iter->second;
	}
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
	UCL::CTokenizer tokenizer(inputData, ":");

	std::string msgId( tokenizer.GetToken(0) );
	std::string msgParameters;
	
	if (2 == tokenizer.GetTokenCount())
	{
		msgParameters = tokenizer.GetToken(1);
	}

	tMsgDeserializers::const_iterator cIter(m_deserializers.find(msgId));

	if (m_deserializers.end() != cIter)
	{
		return cIter->second->Deserialize(msgParameters, bundle);
	}

	bundle.Store( "DATA", inputData );

	return std::string("E_DATA");
}

}
