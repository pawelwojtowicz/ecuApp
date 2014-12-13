#ifndef CGIPROCESSOR_CActionFactory_H
#define CGIPROCESSOR_CActionFactory_H
#include "GlobalTypes.h"
#include "CFactoryItemObject.h"
#include "IAction.h"
namespace CGIProcessor
{
class CProxyProvider;

class CActionFactory
{
  typedef IFactoryItemObject<IAction> tCommandInterface;
  typedef std::map< std::string , tCommandInterface* > tItemFactoryMap;
  typedef tItemFactoryMap::iterator tItemFactoryMapIterator;
public:
  CActionFactory(CProxyProvider&);
  virtual ~CActionFactory();

  IAction* GetCommand( const std::string& commandName );

private:
  tItemFactoryMap m_factoryMap;
};

}

#endif
