project ( ZigBeeDaemon )

SET ( ZIGBEEDAEMON_SRC_DIR ${ECUAPP_SRC}/ZigBeeDaemon)

add_executable ( test_ZigBeeDaemon
${ZIGBEEDAEMON_SRC_DIR}/CCircularATLineExtractor.cpp
Test_CCircularATLineExtractor.cpp
)

target_link_libraries ( test_ZigBeeDaemon ${GTEST_LIBRARIES} rt UCL   )
add_dependencies ( test_ZigBeeDaemon ${GTEST_LIBRARIES} UCL )
