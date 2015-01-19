#include "CActionFactory.h"
#include "CControllerAction.h"
#include "CGetMemInfoAction.h"

namespace CGIProcessor
{

CActionFactory::CActionFactory( CProxyProvider& rProxyProvider)
{
  m_factoryMap.insert( tItemFactoryMap::value_type("controller" , new CFactoryItemObject<IAction, CControllerAction>(rProxyProvider)));
  m_factoryMap.insert( tItemFactoryMap::value_type("getMemInfo", new CFactoryItemObject<IAction, CGetMemInfoAction>(rProxyProvider)));
}

CActionFactory::~CActionFactory()
{
}

IAction* CActionFactory::GetCommand( const std::string& commandName )
{
  IAction* pCommand = 0;

  tItemFactoryMapIterator pIter = m_factoryMap.find(commandName);
  if (m_factoryMap.end() != pIter)
  {
    pCommand = pIter->second->GetObject();
  }

  return pCommand;
}

}
