#include "CActionFactory.h"
#include <UCL/CFastHash.h>
#include "IAction.h"
#include "ICondition.h"

namespace CSM
{
static const UInt32 sUInt32_ActionFactoryHashSeed = 0xFF00FF;

CActionFactory::CActionFactory()
{
}

CActionFactory::~CActionFactory()
{
}

void CActionFactory::AddAction( const std::string& actionName, IAction* pAction )
{
	UInt32 actionNameHash(UCL::CFastHash::CalculateHash32(actionName,sUInt32_ActionFactoryHashSeed));
	
	m_actionMap.insert(tActionMap::value_type(actionNameHash,pAction));
}
	
void CActionFactory::AddCondition ( const std::string& conditionName, ICondition* pCondition )
{
	UInt32 conditionNameHash(UCL::CFastHash::CalculateHash32(conditionName,sUInt32_ActionFactoryHashSeed));
	
	m_conditionMap.insert( tConditionsMap::value_type(conditionNameHash, pCondition));
}
	
IAction* CActionFactory::GetAction( const std::string& actionName ) const
{
	UInt32 actionNameHash(UCL::CFastHash::CalculateHash32(actionName,sUInt32_ActionFactoryHashSeed));
	
	tActionMapConstIterator pCIter = m_actionMap.find(actionNameHash);
	
	if ( m_actionMap.end() != pCIter)
	{
		return pCIter->second;
	}
	
	return 0;
}
	
ICondition* CActionFactory::GetCondition( const std::string& conditionName) const
{
	UInt32 conditionNameHash(UCL::CFastHash::CalculateHash32(conditionName,sUInt32_ActionFactoryHashSeed));
	
	tConditionsMapConstIterator pCIter = m_conditionMap.find(conditionNameHash);
	
	if ( m_conditionMap.end() != pCIter )
	{
		return pCIter->second;
	}
	
	return 0;
}
}
