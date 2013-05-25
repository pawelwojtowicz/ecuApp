#ifndef RUNTIME_CMESSAGE_H
#define RUNTIME_CMESSAGE_H

namespace Runtime
{
class CMessage
{
public:
	CMessage( const char* buffer, size_t size );
	const bool IsValid() const;
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
