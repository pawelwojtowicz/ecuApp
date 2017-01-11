project ( GSMDaemon )

SET( OUTPUT_NAME gsmdaemon )

add_executable ( ${OUTPUT_NAME}
CGSMDaemon.cpp
CGSMDaemonConfiguration.cpp
CModemManager.cpp
CVoiceServiceManager.cpp
CSMSServiceManager.cpp
)

target_link_libraries ( ${OUTPUT_NAME} ControllerInterface Runtime rt Configuration pthread UCL Logger CSM ATProtocolEngine GSMModemSim800L) 
add_dependencies ( ${OUTPUT_NAME} Configuration Logger ControllerInterface Runtime UCL Logger CSM ATProtocolEngine GSMModemSim800L)
install ( TARGETS ${OUTPUT_NAME} RUNTIME DESTINATION ${ECUAPP_RUNTIME_INSTALL_DIR} )
