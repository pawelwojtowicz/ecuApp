#include "CSim800LSerialization.h"
#include <ATProtocolEngine/CParameterBundle.h>
#include <UCL/CTokenizer.h>
#include "IATIncomingMessage.h"
#include "CMGSSerializer.h"
#include "ATDSerializer.h"
#include "CPINSerializer.h"

#include "IATMessageSerializer.h"
#include "CSimpleResponse.h"
#include "CPINResponse.h"
#include "CREGResponse.h"
#include "CMGLResponse.h"
#include "CMGLResponse.h"
#include "CLIPResponse.h"
#include "DTMFResponse.h"
#include "CErrorResponse.h"
#include "CMTIResponse.h"
#include "CSQResponse.h"
#include "COPSResponse.h"


namespace GSMModemSim800L
{

CSim800LSerialization::CSim800LSerialization()
{
	m_serializers.insert(tMsgSerializers::value_type(std::string("CMGS"), new CMGSSerializer() ));	
	m_serializers.insert(tMsgSerializers::value_type(std::string("ATD"), new ATDSerializer() ));
	m_serializers.insert(tMsgSerializers::value_type(std::string("CPIN"), new CPINSerializer() ));

	m_deserializers.insert(tMsgDeserializers::value_type(std::string("> OK"), new CSimpleResponse("E_SMS_OK") ) );
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("> ERROR"), new CSimpleResponse("E_SMS_ERROR") ) );
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("OK"), new CSimpleResponse("E_OK") ) );
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("AT\rOK"), new CSimpleResponse("E_OK_WITH_ECHO") ) );	
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("RING"), new CSimpleResponse("E_INCOMING_CALL") ) );
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("NO CARRIER"), new CSimpleResponse("E_NO_CARRIER") ) );
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("NO DIALTONE"), new CSimpleResponse("E_NO_DIALTONE") ) );
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("NO ANSWER"), new CSimpleResponse("E_NO_ANSWER") ) );
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("BUSY"), new CSimpleResponse("E_BUSY") ) );
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("+CPIN"), new CPINResponse() ) );
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("+CREG"), new CREGResponse() ) );
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("+CMGL"), new CMGLResponse() ) );
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("+CLIP"), new CLIPResponse() ) );
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("+CMTI"), new CMTIResponse() ) );
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("+CME ERROR"), new CErrorResponse() ) );
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("+CSQ"), new CSQResponse() ) );
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("+COPS"), new COPSResponse() ) );
	m_deserializers.insert(tMsgDeserializers::value_type(std::string("+DTMF"), new DTMFResponse() ) );
}

CSim800LSerialization::~CSim800LSerialization()
{
	for(tMsgSerializers::iterator iter = m_serializers.begin() ; m_serializers.end() != iter ; ++iter )
	{
		delete iter->second;
	}

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

bool CSim800LSerialization::SerializeMsg( const std::string& msgId, const ATProtocolEngine::CParameterBundle& bundle, std::string& msgText )
{
	tMsgSerializers::const_iterator foundSerializerIt( m_serializers.find(msgId) );

	if ( m_serializers.end() != foundSerializerIt )
	{
		return foundSerializerIt->second->Serialize( bundle, msgText);
	}

	return false;
}

const std::string CSim800LSerialization::Deserialize( const std::string& inputData, ATProtocolEngine::CParameterBundle& bundle)
{
	UCL::CTokenizer tokenizer(inputData, ":");

	std::string msgId( tokenizer.GetToken(0) );
	
	tMsgDeserializers::const_iterator cIter(m_deserializers.find(msgId));

	if (m_deserializers.end() != cIter)
	{
		return cIter->second->Deserialize(inputData, bundle);
	}

	bundle.Store( "DATA", inputData );

	return std::string("E_DATA");
}

}
