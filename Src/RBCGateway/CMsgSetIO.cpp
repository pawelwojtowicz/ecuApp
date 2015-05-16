#include "CMsgSetIO.h"

namespace RBCGateway
{

CMsgSetIO::CMsgSetIO()
: CMsgBase(moduleInvalid, cmdSetIO)
, m_portID(0)
, m_ioState(0)
{
}

CMsgSetIO::~CMsgSetIO()
{
}
	
void CMsgSetIO::SetPort(const UInt8 portID)
{
	m_portID = portID;
}

void CMsgSetIO::SetIO( const UInt8 ioID, const bool ioState)
{
	UInt8 mask(0x01);
	mask= mask<<ioID;	
	
	if ( ioState )
	{
		m_ioState |= mask;
	}
	else
	{
		m_ioState &= (~mask);
	}
}
	
size_t CMsgSetIO::GetPayloadSize()
{
	return 3;
}	

void CMsgSetIO::SerializePayload()
{
	PutUnsignedHASCII(m_portID, 1);
	PutUnsignedHASCII(m_ioState, 2);
}

}
