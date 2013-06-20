#include "CController.h"
#include "Runtime/CMessage.h"

CController gs;

CController::CController()
: CExecutable("TestProcess")
{

}

Int32 CController::Run()
{

	if (m_messager.Initialize("/ControllerQueue") )
	{
		printf("Udalo sie - controller otworzyl kolejke\n");
	}

	Int32 a, b, c;
	m_messager.GetQueueParameters(a,b,c);
	printf("%d %d %d", a, b, c);
	
	if (m_messager.SubscribeMessage( 0, msgId_Controller_TestMessage, this ) )
	{
		printf("Zarejestrowani na mesecz\n");
	}

	m_messager.StartMsgProcessor();

	return 0;
}

void CController::HandleMessage( Runtime::CMessage& message )
{
	printf("wszedl tutaj - jest nowy messecz\n");
	std::string tekstMsga;
	message.GetValue(tekstMsga);
	UInt32 value(0);
	message.GetValue( value );

	printf("dane z MSGA [%s], [%d]\n", tekstMsga.c_str(), value);
}
