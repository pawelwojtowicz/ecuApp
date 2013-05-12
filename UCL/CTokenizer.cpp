#include "CTokenizer.h"
#include <cstring>

namespace UCL
{
CTokenizer::CTokenizer( const char* stringBuffer, const size_t bufferSize, const char* delimiter )
{
	if ( 0 != stringBuffer && bufferSize > 0 )
	{
		Tokenize( stringBuffer, bufferSize, delimiter);
	}
}

CTokenizer::CTokenizer( const std::string& inpString , const char* delimiter )
{
	unsigned int bufferSize = inpString.length()+1;

	if (bufferSize > 1)
	{
		Tokenize( inpString.c_str(), bufferSize, delimiter );
	}
}

CTokenizer::~CTokenizer()
{
}

void CTokenizer::Tokenize( const char* stringBuffer, const size_t bufferSize, const char* delimiter )
{
	const char* begin = (stringBuffer);
	char* cur 	= const_cast<char*>(stringBuffer);
	const char* end(stringBuffer+bufferSize);
	size_t delLength = strlen(delimiter);

	while ( cur < end && *cur != '\0' )
	{
		bool delFound(false);
		for (size_t i = 0 ; i < delLength ; ++i )
		{
			if (*cur == delimiter[i] )
			{
				delFound=true;
				break;
			}
		}
		
		if ( delFound )
		{
			std::string token(begin, cur-begin );
			
			m_tokenizedFields.push_back(token);

			if ( ( cur+1 ) < end )
			{
				begin = cur + 1;
			}
		}

		++cur;
	}

	if ( '\0' == *cur && cur > begin  )
	{
		std::string token(begin, cur-begin );		
		m_tokenizedFields.push_back(token);		
	}

}


unsigned int CTokenizer::GetTokenCount()
{
	return m_tokenizedFields.size();
}


const std::string& CTokenizer::GetToken(const unsigned int& index )
{
	static std::string empty("");

	if (m_tokenizedFields.size() > index )
	{
		return m_tokenizedFields[index];
	}

	return empty;
}

}
