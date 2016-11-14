project( Runtime )

SET( OUTPUT_NAME Runtime )

add_library( ${OUTPUT_NAME} SHARED
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

target_link_libraries ( ${OUTPUT_NAME} ControllerInterface ) 
add_dependencies ( ${OUTPUT_NAME} ControllerInterface )
install ( TARGETS ${OUTPUT_NAME} LIBRARY DESTINATION ${ECUAPP_LIBRARY_INSTALL_DIR} )
