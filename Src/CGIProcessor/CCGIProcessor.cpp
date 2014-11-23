#include "CCGIProcessor.h"
#include "CGIProcessorConst.h"
#include "CCommandFactory.h"
#include "JSONLib/json.h"


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
  printf("Content-type: application/json\r\n");
  printf("\r\n");
  
  // prepare the structure for returning the JSON data
  json::Object requestResponse;

  std::string commandName = m_environment.GetVariable(s_const_sv_commandName);
  
  
  ICommand* pCommand = m_commandFactory.GetCommand(commandName);
  if ( 0 != pCommand )
  {
    bool retVal(pCommand->Execute(m_environment));

    json::Object commandExecutionResults;
    
    commandExecutionResults["CommandName"] = commandName.c_str();
    commandExecutionResults["Result"] = retVal;
    
    requestResponse["CommandExecution"]=commandExecutionResults;
  }
  
  // serialize the JSON into the string, and send it to the std output.
  std::string jsonInString(json::Serialize(requestResponse));
  printf("%s", jsonInString.c_str() );
  
  return 0;
}

void CCGIProcessor::Shutdown()
{
  printf("Shutdown\r\n");
}

}

