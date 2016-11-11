project( Runtime )

add_library( Runtime SHARED
CExecutable.cpp
executableMain.cpp
CHealthReporter.cpp
CMessage.cpp
CMessenger.cpp
CProxyBase.cpp
CRuntimeUnit.cpp
CSharedStorage.cpp
CStubBase.cpp
CTimerManager.cpp
)