#include "CCGIProcessor.h"
#include "CGIProcessorConst.h"
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
  m_proxyProvider.Initialize();
}

Int32 CCGIProcessor::Run()
{
  // there has to be written those 2 lines to be able to see something on the
  printf("Content-type: application/json\r\n");
  printf("\r\n");
  
  // prepare the structure for returning the JSON data
  json::Object requestResponse;

  const std::string& commandName 	= m_environment.GetVariable(s_const_sv_commandName);
  const std::string& apiName			= m_environment.GetVariable(s_const_sv_apiName);
  
  
  IAction* pCommand = m_commandFactory.GetCommand(commandName);
  if ( 0 != pCommand )
  {
		json::Object commandExecutionResults;
		json::Object commandData;

    bool retVal(pCommand->Execute(m_environment, commandData));

    commandExecutionResults["data"] = commandData; 
    commandExecutionResults["result"] = retVal;
    
    requestResponse[apiName.c_str()]=commandExecutionResults;
  }
  
  // serialize the JSON into the string, and send it to the std output.
  std::string jsonInString(json::Serialize(requestResponse));
  printf("%s", jsonInString.c_str() );
  
  return 0;
}

void CCGIProcessor::Shutdown()
{
	m_proxyProvider.Shutdown();
}

}

