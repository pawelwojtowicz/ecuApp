#ifndef UCL_CTHREAD_H
#define UCL_CTHREAD_H
#include <pthread.h>
#include <string>

namespace UCL
{

class CThread
{
public:
	CThread( const std::string& threadName = "" );
	virtual ~CThread();

	void Start();
	void Terminate();

	bool WaitFor();


	virtual void Run()=0;

protected:
	void AllowTermination(const bool allowFlag);

	const std::string& GetThreadName() {return m_threadName;};

private:
	static void* ThreadRunner( void* pThreadInstance );

	virtual void CleanUp() {} ;
private:
	const std::string m_threadName;

	pthread_t m_threadHandle;

	int m_cancellationState;

	int m_cancellationType;
};

}
#endif
