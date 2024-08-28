add_library(fb-modbus-master INTERFACE)

target_sources(fb-modbus-master
    INTERFACE
        ./ModbusMaster.cpp
)

target_include_directories(fb-modbus-master
    INTERFACE
        .
)

target_link_libraries(fb-modbus-master INTERFACE 
    mbed-rs485
)