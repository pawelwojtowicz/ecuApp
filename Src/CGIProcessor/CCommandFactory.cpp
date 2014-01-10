#include "CCommandFactory.h"
#include "CControllerCommand.h"

namespace CGIProcessor
{

CCommandFactory::CCommandFactory( CProxyProvider& rProxyProvider)
{
  m_factoryMap.insert( tItemFactoryMap::value_type("controller" , new CFactoryItemObject<ICommand, CControllerCommand>(rProxyProvider)));
}

CCommandFactory::~CCommandFactory()
{
}

ICommand* CCommandFactory::GetCommand( const std::string& commandName )
{
  ICommand* pCommand = 0;

  tItemFactoryMapIterator pIter = m_factoryMap.find(commandName);
  if (m_factoryMap.end() != pIter)
  {
    pCommand = pIter->second->GetObject();
  }

  return pCommand;
}

}
