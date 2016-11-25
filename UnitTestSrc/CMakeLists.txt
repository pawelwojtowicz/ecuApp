project (UnitTestSrc )

add_compile_options( -Wall -pedantic -std=c++0x )

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${ECU_APP_TARGET_DIR}/usr/bin/unitTests )
SET( GTEST_LIBRARIES gtest gmock gtest_main gmock_main )

include_directories ( ${GMOCK_DIR}/include )
include_directories ( ${GMOCK_DIR}/gtest/include )
include_directories ( ${ECUAPP_SRC} )
include_directories ( ${ECUAPP_SRC}/Global)


add_subdirectory ( Controller )
add_subdirectory ( ControllerInterface )
add_subdirectory ( CSM )
add_subdirectory ( JSONLib )
add_subdirectory ( Runtime )
add_subdirectory ( UCL )
