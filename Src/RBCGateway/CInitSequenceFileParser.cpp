#include "CInitSequenceFileParser.h"
#include <stdio.h>
#include <UCL/CTokenizer.h>
#include "IMsgFactory.h"

namespace RBCGateway
{
CInitSequenceFileParser::CInitSequenceFileParser( IMsgFactory& msgFactory )
: m_msgFactory( msgFactory )
{
}

CInitSequenceFileParser::~CInitSequenceFileParser()
{
}

tMsgList CInitSequenceFileParser::ParseFile(const std::string& fileName)
{
	tMsgList initSequence;
	FILE* configSequenceFilePointer = fopen( fileName.c_str() , "r");
	
	char arguments[200];
	
	if ( 0 != configSequenceFilePointer )
	{
		UInt8 readValues( fscanf(configSequenceFilePointer, "%s\n",arguments));
		
		while (1==readValues)
		{
			UCL::CTokenizer tokenizedArguments(arguments,200, "(,)");
			
			CMsgBase* pMsgInstance = m_msgFactory.CreateMessage(tokenizedArguments.GetTokens());
			if ( 0 != pMsgInstance )
			{
				initSequence.push_back(pMsgInstance);
				readValues = fscanf(configSequenceFilePointer, "%s\n",arguments);
			}
			else
			{
				readValues = 0;
			}
		}
		fclose(configSequenceFilePointer);
	}
	return initSequence;
}

}
