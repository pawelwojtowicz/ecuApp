#ifndef UCL_CSEMAPHORE_H
#define UCL_CSEMAPHORE_H
#include <semaphore.h>
#include <GlobalTypes.h>

namespace UCL
{

class CSemaphore
{
public:
	CSemaphore();
	virtual ~CSemaphore();
	
	bool Initialize(const std::string&, const UInt32 semaphoreCount);
	void Shutdown ();
	
	void Lock();
	void Unlock();
	
private:
	CSemaphore(const CSemaphore&);
	CSemaphore& operator=( const CSemaphore&);
	
private:
	sem_t* m_lockHandle;
};

}
#endif
