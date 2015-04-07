#ifndef TTS_CTTSSTUB_H
#define TTS_CTTSSTUB_H

#include <Runtime/CStubBase.h> 

#include <Runtime/CSharedStorage.h>

namespace Runtime
{
class CMessenger;
class CMessage;
}

namespace TTS
{
class ITTSServices;

class CTTSStub: public Runtime::CStubBase
{
public:
	CTTSStub( Runtime::IMessenger& rMessenger );
	virtual ~CTTSStub();

	virtual bool Initialize(ITTSServices* pControllerServices);
	virtual bool Shutdown(); 	

private:
	virtual void HandleMessage(Runtime::CMessage& rMessage);

private:
	ITTSServices* m_pTTSServices;
	
};

}
#endif //TTS_CTTSSTUB_H
