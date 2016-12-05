project ( ATProtocolEngine )

SET ( ATPROTOCOLENGINE_SRC_DIR ${ECUAPP_SRC}/ATProtocolEngine)

add_executable ( test_ATProtocolEngine
${ATPROTOCOLENGINE_SRC_DIR}/CCircularATLineExtractor.cpp
Test_CCircularATLineExtractor.cpp
)

target_link_libraries ( test_ATProtocolEngine ${GTEST_LIBRARIES} rt UCL   )
add_dependencies ( test_ATProtocolEngine ${GTEST_LIBRARIES} UCL )
