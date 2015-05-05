#ifndef UCL_CTOKENIZER_H
#define UCL_CTOKENIZER_H

#include "GlobalTypes.h"

namespace UCL
{
class CTokenizer
{
public:
	CTokenizer( const char* stringBuffer, const size_t bufferSize, const char* delimiter );
	CTokenizer( const std::string& stringBuffer , const char* delimiter );

	virtual ~CTokenizer();

	unsigned int GetTokenCount();
	const std::string& GetToken(const unsigned int& index );
	const tStringVector& GetTokens() { return m_tokenizedFields; }; 

private:
	void Tokenize( const char* stringBuffer, const size_t bufferSize, const char* delimiter );
	tStringVector m_tokenizedFields;
};
}

#endif //UCL_CTOKENIZER_H
