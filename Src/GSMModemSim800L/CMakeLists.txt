project (GSMModemSim800L)

add_compile_options( -fPIC )

add_library( GSMModemSim800L STATIC CModemProtocolLogic.cpp CSim800LSerialization.cpp COKResponse.cpp CPINResponse.cpp)
