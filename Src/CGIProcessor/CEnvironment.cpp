#include "CEnvironment.h"
#include "CGIProcessorConst.h"
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <UCL/SystemEnvironment.h>
#include <UCL/CTokenizer.h>
 

namespace CGIProcessor
{
CEnvironment::CEnvironment()
{
}

CEnvironment::~CEnvironment()
{
}

void CEnvironment::Initialize()
{
  std::string requestMethod(UCL::SystemEnvironment::GetVariable(s_const_reqMethod));

  if ( 0 == requestMethod.compare(s_const_get_reqMethod) )
  {
    Extract_GET_Environment();
  }
  else if ( 0 == requestMethod.compare(s_const_post_reqMethod) )
  {
    Extract_POST_Environment();
  }
  else
  {
    printf("Request method [%s] not recognized\n ", requestMethod.c_str() );
  }
}

const std::string& CEnvironment::GetVariable(const std::string& variableName )
{
  tVariablesConstIter pCIter = m_name2valueVariableMap.find(variableName);

  if ( m_name2valueVariableMap.end() != pCIter )
  {
    return pCIter->second;
  }

  return s_cEmptyString;
}

void CEnvironment::Extract_POST_Environment()
{
  UInt32 inputLength(atoi(UCL::SystemEnvironment::GetVariable(s_const_contentLength).c_str() ) );

  Int8* inputBuffer = new Int8[ inputLength+1 ];

  if ( 0 != inputBuffer )
  {
    memset(inputBuffer, 0, inputLength+1);

    if ( inputLength == fread(inputBuffer, 1,inputLength, stdin ) )
    {
      printf("Read correct amount of data\n");
      std::string argumentList(inputBuffer);
      delete [] inputBuffer;

      UCL::CTokenizer nameValuePairTokens(argumentList, "&");
      UInt8 variableCount( nameValuePairTokens.GetTokenCount() );

      for (UInt8 index = 0 ; index < variableCount ; ++index )
      {
        UCL::CTokenizer nameValueTokens( nameValuePairTokens.GetToken(index) , "=" );
        if ( 2 == nameValueTokens.GetTokenCount() )
        {
          printf("Extracted correct values [%s] [%s]<//br>", nameValueTokens.GetToken(0).c_str(), nameValueTokens.GetToken(1).c_str());
          m_name2valueVariableMap.insert( tVariablesMap::value_type(nameValueTokens.GetToken(0), nameValueTokens.GetToken(1) ) );
        }
      }
    }
  }  
}

void CEnvironment::Extract_GET_Environment()
{
  std::string argumentList( UCL::SystemEnvironment::GetVariable(s_const_parameters) );

  UCL::CTokenizer nameValuePairTokens(argumentList, "&");
  UInt8 variableCount( nameValuePairTokens.GetTokenCount() );

  for (UInt8 index = 0 ; index < variableCount ; ++index )
  {
    UCL::CTokenizer nameValueTokens( nameValuePairTokens.GetToken(index) ,"=");
    if ( 2 == nameValueTokens.GetTokenCount() )
    {
      printf("Extracted correct values [%s] [%s]<//br>", nameValueTokens.GetToken(0).c_str(), nameValueTokens.GetToken(1).c_str());
      m_name2valueVariableMap.insert( tVariablesMap::value_type(nameValueTokens.GetToken(0), nameValueTokens.GetToken(1) ) );
    }
  }
}


}
