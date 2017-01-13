project ( GSMModemSim800L )

SET ( GSMMODEMSIM800L_SRC_DIR ${ECUAPP_SRC}/GSMModemSim800L)

add_executable ( test_GSMModem800L test_CSim800LSerialization.cpp
)

target_link_libraries ( test_GSMModem800L ${GTEST_LIBRARIES} rt UCL CSM ATProtocolEngine GSMModemSim800L)
add_dependencies ( test_GSMModem800L ${GTEST_LIBRARIES} UCL CSM ATProtocolEngine GSMModemSim800L)
