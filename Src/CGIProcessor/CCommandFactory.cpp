#include "CCommandFactory.h"
#include "CDummyCommand.h"

namespace CGIProcessor
{

CCommandFactory::CCommandFactory()
{
  m_factoryMap.insert( tItemFactoryMap::value_type("dummy" , new CFactoryItemObject<ICommand, CDummyCommand>()));
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
