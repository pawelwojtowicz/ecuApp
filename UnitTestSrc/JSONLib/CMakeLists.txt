project ( JSONLibTest )

SET ( JSONLIB_SRC_DIR ${ECUAPP_SRC}/JSONLib)

add_executable ( test_JSONLib
test_JSON.cpp
${JSONLIB_SRC_DIR}/json.cpp
)

target_link_libraries ( test_JSONLib ${GTEST_LIBRARIES} )
add_dependencies ( test_JSONLib ${GTEST_LIBRARIES} )
