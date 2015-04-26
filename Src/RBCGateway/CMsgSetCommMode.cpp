#include "CMsgSetCommMode.h"

namespace RBCGateway
{
CMsgSetCommMode::CMsgSetCommMode()
: CMsgBase( moduleHUB, cmdSetCommMode )
, m_communicationMode(mode_Transparent)
{
}

CMsgSetCommMode::~CMsgSetCommMode()
{
}
	
void CMsgSetCommMode::SetCommunicationMode(const tCommunicationMode mode )
{
	m_communicationMode = mode;
}
	
size_t CMsgSetCommMode::GetPayloadSize()
{
	// one hascii for the mode.
	return 3;
}
	
void CMsgSetCommMode::SerializePayload()
{
	PutUnsignedHASCII(static_cast<UInt32>(m_communicationMode),3);
}

}

