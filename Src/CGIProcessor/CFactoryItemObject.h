#ifndef CGIPROCESSOR_CFACTORYITEMOBJECT_H
#define CGIPROCESSOR_CFACTORYITEMOBJECT_H

namespace CGIProcessor
{

template <class INTERFACE>
class IFactoryItemObject
{
public:
  IFactoryItemObject() {};
  virtual ~IFactoryItemObject() {};

  virtual INTERFACE* GetObject() = 0;
private:
  IFactoryItemObject(const IFactoryItemObject&);
  IFactoryItemObject& operator=(const IFactoryItemObject&);
};

template <class INTERFACE, class ITEM>
class CFactoryItemObject : public IFactoryItemObject<INTERFACE>
{
public:
  CFactoryItemObject()
  : m_objectInterface(0)
  {
  }

  INTERFACE* GetObject()
  {
    if ( 0 == m_objectInterface )
    {
      m_objectInterface = new ITEM(); 
    }
    
    return m_objectInterface;
  }
  
  virtual ~CFactoryItemObject()
  {
    delete m_objectInterface;
  }

private:
  INTERFACE* m_objectInterface;
};
}

#endif
