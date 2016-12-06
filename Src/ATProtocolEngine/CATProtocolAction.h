#pragma once
#include <CSM/IAction.h>

namespace ATProtocolEngine
{
class CParameterBundle;

class CATProtocolAction: public CSM::IAction
{
public:
	CATProtocolAction()
	: m_parameterBundle(0)
	{
	};

	CATProtocolAction( CParameterBundle* pBundle )
	: m_parameterBundle( pBundle)	
	{
	};

	virtual ~CATProtocolAction()
	{
	};
	
	void SetBundle( CParameterBundle* pBundle)
	{
		m_parameterBundle = pBundle;
	};

protected:
	CParameterBundle* GetParameterBundle()
	{
		return m_parameterBundle;
	};

private:
	CParameterBundle* m_parameterBundle;
};
}
