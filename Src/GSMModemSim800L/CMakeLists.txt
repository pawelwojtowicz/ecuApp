project (GSMModemSim800L)

add_compile_options( -fPIC )

add_library( GSMModemSim800L STATIC 
CModemProtocolLogic.cpp 
CSim800LSerialization.cpp 
CSimpleResponse.cpp 
CPINResponse.cpp
CREGResponse.cpp
CMGLResponse.cpp
CLIPResponse.cpp
CErrorResponse.cpp
CMTIResponse.cpp
CMGSSerializer.cpp
ATDSerializer.cpp
CPINSerializer.cpp
CGSMModemActionFactory.cpp
CGSMActionContext.cpp
CActionNotifySMSSent.cpp
CActionNotifySMSSendFailure.cpp
CActionNotifyIncomingSMS.cpp )
