project (UnitTestSrc )

add_compile_options( -Wall -pedantic -std=c++0x )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${ECU_APP_TARGET_DIR}/unitTests )
SET( GTEST_LIBRARIES gtest gmock gtest_main gmock_main )

include_directories ( ${GMOCK_DIR}/include )
include_directories ( ${GMOCK_DIR}/gtest/include )
include_directories ( ${ECU_APP_SRC} )
include_directories ( ${ECU_APP_SRC}/Global)


add_subdirectory ( Controller )