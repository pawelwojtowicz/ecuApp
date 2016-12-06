project (ATProtocolEngine)

SET(OUTPUT_NAME ATProtocolEngine )

add_library( ${OUTPUT_NAME} SHARED 
CCircularATLineExtractor.cpp
CParameterBundle.cpp
CATProtocolAction.cpp
CATProtocolEngine.cpp
CATProtocolActionFactory.cpp
CSerialPortHandler.cpp
)

install ( TARGETS ${OUTPUT_NAME} LIBRARY DESTINATION ${ECUAPP_LIBRARY_INSTALL_DIR} )
