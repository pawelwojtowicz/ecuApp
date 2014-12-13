#ifndef CGIPROCESSOR_CCGIPROCESSOR_H
#define CGIPROCESSOR_CCGIPROCESSOR_H

#include <Runtime/CExecutable.h>
#include "CProxyProvider.h"
#include "CActionFactory.h"
#include "CEnvironment.h"

namespace CGIProcessor
{

class CCGIProcessor: public Runtime::CExecutable
{
public:
  CCGIProcessor();
  virtual ~CCGIProcessor();

	virtual void Initialize();
	virtual Int32 Run();
	virtual void Shutdown();

private:
  CCGIProcessor(const CCGIProcessor&);
  CCGIProcessor& operator=(const CCGIProcessor&);

  CProxyProvider m_proxyProvider;

  CActionFactory m_commandFactory;

  CEnvironment m_environment;

};

}

#endif //CGIPROCESSOR_CCGIPROCESSOR_H
