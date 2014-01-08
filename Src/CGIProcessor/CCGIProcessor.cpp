#include "CCGIProcessor.h"
#include "CGIProcessorConst.h"

#include <stdio.h>

CGIProcessor::CCGIProcessor gs;

namespace CGIProcessor
{

CCGIProcessor::CCGIProcessor()
: Runtime::CExecutable( "CGIProcessor" )
{

}

CCGIProcessor::~CCGIProcessor()
{

}

void CCGIProcessor::Initialize()
{
printf("Content-type: text/plain\r\n");
  m_environment.Initialize();
}

Int32 CCGIProcessor::Run()
{
  return 0;
}

void CCGIProcessor::Shutdown()
{
  printf("Shutdown\r\n");
}

}

