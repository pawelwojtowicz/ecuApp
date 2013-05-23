#ifndef RUNTIME_CMESSAGE_H
#define RUNTIME_CMESSAGE_H

namespace Runtime
{
class CMessage
{
	const std::string& GetTargetName() const;
	const unsigned GetPrio() const;
	const char* GetBuffer() const;
	const size_t GetSize() const;
	const int GetMsgId() const;

	void Reset();
private:
};
}

#endif
