#ifndef RBCGATEWAY_CINITSEQUENCEFILEPARSER_H
#define RBCGATEWAY_CINITSEQUENCEFILEPARSER_H
#include <GlobalTypes.h>
#include "CMsgBase.h"

namespace RBCGateway
{
class CMsgBase;
class IMsgFactory;

class CInitSequenceFileParser
{
public:
	CInitSequenceFileParser( IMsgFactory& msgFactory );
	virtual ~CInitSequenceFileParser();
	
	tMsgList ParseFile(const std::string& fileName);
	
private:
	CInitSequenceFileParser(const CInitSequenceFileParser&);
	CInitSequenceFileParser& operator=(const CInitSequenceFileParser&);
	
	IMsgFactory& m_msgFactory;
};
}
#endif
