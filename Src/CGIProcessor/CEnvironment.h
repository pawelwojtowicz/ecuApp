#ifndef CGIPROCESSOR_CENVIRONMENT_H
#define CGIPROCESSOR_CENVIRONMENT_H
#include <Global/GlobalTypes.h>

namespace CGIProcessor
{
class CEnvironment
{
public:
  CEnvironment();
  virtual ~CEnvironment();

  void Initialize();

  const std::string& GetVariable(const std::string& variableName ) const;

private:
  void Extract_POST_Environment();
  void Extract_GET_Environment();

private:
  tVariablesMap m_name2valueVariableMap;
};
}

#endif
