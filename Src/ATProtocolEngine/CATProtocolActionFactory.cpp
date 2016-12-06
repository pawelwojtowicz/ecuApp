#include "CATProtocolActionFactory.h"
#include <CSM/IAction.h>
#include <CSM/ICondition.h>
#include "CATProtocolAction.h"
#include <UCL/CTokenizer.h>

namespace ATProtocolEngine
{

CATProtocolActionFactory::CATProtocolActionFactory()
{
}

CATProtocolActionFactory::~CATProtocolActionFactory()
{
}

void CATProtocolActionFactory::RegisterAction( const std::string& actionName, CATProtocolAction* pAction )
{
	m_nameToActionMap.insert( tNameToActionMap::value_type(actionName, pAction) );

}

CSM::IAction* CATProtocolActionFactory::GetAction( const std::string& actionName ) const
{
	UCL::CTokenizer actionGroup(actionName, ";");
	UInt32 tokenCount( actionGroup.GetTokenCount() );

	return 0;
}
	
CSM::ICondition* CATProtocolActionFactory::GetCondition( const std::string& conditionName) const
{
	return 0;
}
}
