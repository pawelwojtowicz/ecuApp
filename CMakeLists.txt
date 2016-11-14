cmake_minimum_required( VERSION 2.8 )

project (ecuAppBundle)

SET( BUILD_UNIT_TESTS OFF )

include ( .settings OPTIONAL )

SET( GMOCK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/gmock-1.7.0 )
SET( ECUAPP_SRC ${CMAKE_CURRENT_SOURCE_DIR}/Src )
SET( ECUAPP_RUNTIME_INSTALL_DIR usr/bin )
SET( ECUAPP_LIBRARY_INSTALL_DIR usr/lib )

add_subdirectory( ${ECUAPP_SRC} )

if (BUILD_UNIT_TESTS)
  add_subdirectory( ${GMOCK_DIR} )
  add_subdirectory( UnitTestSrc )
endif()