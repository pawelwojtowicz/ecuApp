#pragma once
#include <Global/GlobalTypes.h>
#include <CSM/IActionFactory.h>
#include <CSM/IAction.h>
#include "IActionExecutionContext.h"



namespace ATProtocolEngine
{

class CATProtocolAction: public CSM::IAction
{
public:
	CATProtocolAction(IActionExecutionContext& executionContext)
	: m_rExecutionContext(executionContext)
	{
	};

	virtual ~CATProtocolAction()
	{
	};

 	virtual bool Configure( const CSM::IActionFactory& ,const std::string& )
	{
		return true;
	}
	
protected:
	IActionExecutionContext& GetExecutionContext()
	{
		return m_rExecutionContext;
	}

private:
	IActionExecutionContext& m_rExecutionContext;
};
}
