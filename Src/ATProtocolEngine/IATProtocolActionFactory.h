#pragma once
#include <Global/GlobalTypes.h>

namespace ATProtocolEngine
{
class CATProtocolAction;

class IATProtocolActionFactory
{
public:
	IATProtocolActionFactory() {};
	virtual ~IATProtocolActionFactory() {};

	virtual CATProtocolAction* CreateActionInstance( const std::string& actionName ) const = 0;
};
}
