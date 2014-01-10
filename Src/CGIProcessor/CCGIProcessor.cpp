#include "CCGIProcessor.h"
#include "CGIProcessorConst.h"
#include "CCommandFactory.h"


#include <stdio.h>

CGIProcessor::CCGIProcessor gs;

namespace CGIProcessor
{

CCGIProcessor::CCGIProcessor()
: Runtime::CExecutable( "CGIProcessor" )
, m_commandFactory(m_proxyProvider)
{

}

CCGIProcessor::~CCGIProcessor()
{

}

void CCGIProcessor::Initialize()
{
  m_environment.Initialize();
}

Int32 CCGIProcessor::Run()
{
  // there has to be written those 2 lines to be able to see something on the
  printf("Content-type: text/plain\r\n");
  printf("\r\n");

  std::string commandName = m_environment.GetVariable(s_const_sv_commandName);
  printf( "Dostalem komende %s\n", commandName.c_str() );
  
  ICommand* pCommand = m_commandFactory.GetCommand(commandName);
  if ( 0 != pCommand )
  {
    bool retVal(pCommand->Execute(m_environment));

    printf( "znalazlem i wykonalem komende %d\n", retVal);
  }
  return 0;
}

void CCGIProcessor::Shutdown()
{
  printf("Shutdown\r\n");
}

}

