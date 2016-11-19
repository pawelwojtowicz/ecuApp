cmake_minimum_required( VERSION 3.0 )

project (ecuAppBundle)

SET( BUILD_UNIT_TESTS OFF )

include ( .settings OPTIONAL )

SET( GMOCK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/gmock-1.7.0 )
SET( ECUAPP_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} ) 
SET( ECUAPP_SRC ${CMAKE_CURRENT_SOURCE_DIR}/Src )
SET( ECUAPP_RUNTIME_INSTALL_DIR bin )
SET( ECUAPP_LIBRARY_INSTALL_DIR lib )

add_subdirectory( DeploymentScripts )
add_subdirectory( ${ECUAPP_SRC} )

if (BUILD_UNIT_TESTS)
  add_subdirectory( ${GMOCK_DIR} )
  add_subdirectory( UnitTestSrc )
endif()
