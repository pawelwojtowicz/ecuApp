project (ATProtocolEngine)

SET(OUTPUT_NAME ATProtocolEngine )

add_library( ${OUTPUT_NAME} SHARED 
CCircularATLineExtractor.cpp
CParameterBundle.cpp
CATProtocolAction.cpp
CATProtocolEngine.cpp
CATProtocolActionFactory.cpp
CSerialPortHandler.cpp
CSendAction.cpp
CStartTimeoutAction.cpp
CStopTimeoutAction.cpp
CCompositeAction.cpp
CStoreAction.cpp
COpenPortAction.cpp
CClosePortAction.cpp
CStartAction.cpp
CStopAction.cpp
CResetParamAction.cpp
CSetParamAction.cpp
)

target_link_libraries ( ${OUTPUT_NAME} pthread UCL Logger CSM ) 
add_dependencies ( ${OUTPUT_NAME} UCL Logger CSM)

install ( TARGETS ${OUTPUT_NAME} LIBRARY DESTINATION ${ECUAPP_LIBRARY_INSTALL_DIR} )
