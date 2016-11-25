project ( ControllerInterface )

add_compile_options( -fPIC )

add_library ( ControllerInterface STATIC
  
CControllerProxy.cpp
CControllerStub.cpp
CPublicProcessInfo.cpp
)