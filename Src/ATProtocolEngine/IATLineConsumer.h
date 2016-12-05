#pragma once
#include <Global/GlobalTypes.h>

namespace ATProtocolEngine
{
class IATLineConsumer
{
public:
	IATLineConsumer() {};
	virtual ~IATLineConsumer() {};

	virtual void NotifyATResponseExtracted( const std::string line ) = 0;

	virtual void NotifyATPromptExtracted( const std::string line ) = 0;

private:
	IATLineConsumer(const IATLineConsumer&);
	IATLineConsumer& operator=(const IATLineConsumer&);
};
}
