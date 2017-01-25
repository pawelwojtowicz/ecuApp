project ( GSMDaemonInterface )

add_compile_options( -fPIC )

add_library ( GSMDaemonInterface STATIC
CGSMDaemonStub.cpp
)
