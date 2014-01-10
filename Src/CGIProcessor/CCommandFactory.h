#ifndef CGIPROCESSOR_CCOMMANDFACTORY_H
#define CGIPROCESSOR_CCOMMANDFACTORY_H
#include "GlobalTypes.h"
#include "CFactoryItemObject.h"
#include "ICommand.h"
namespace CGIProcessor
{
class CProxyProvider;

class CCommandFactory
{
  typedef IFactoryItemObject<ICommand> tCommandInterface;
  typedef std::map< std::string , tCommandInterface* > tItemFactoryMap;
  typedef tItemFactoryMap::iterator tItemFactoryMapIterator;
public:
  CCommandFactory(CProxyProvider&);
  virtual ~CCommandFactory();

  ICommand* GetCommand( const std::string& commandName );

private:
  tItemFactoryMap m_factoryMap;
};

}

#endif
