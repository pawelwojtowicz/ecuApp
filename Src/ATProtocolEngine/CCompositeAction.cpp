#include "CCompositeAction.h"
#include <algorithm>

namespace ATProtocolEngine
{
CCompositeAction::CCompositeAction()
{
}

CCompositeAction::~CCompositeAction()
{
}

void CCompositeAction::Execute()
{
	std::for_each(m_actions.begin(), m_actions.end(), std::mem_fun(&CSM::IAction::Execute));
}

}
