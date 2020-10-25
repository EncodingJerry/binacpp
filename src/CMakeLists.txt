cmake_minimum_required (VERSION 3.0.0)
project (binacpp VERSION 1.0.0 DESCRIPTION "binance description")


add_library(binacpp SHARED
    binacpp.cpp
    binacpp.h
    binacpp_logger.cpp
    binacpp_logger.h
    binacpp_utils.cpp
    binacpp_utils.h
    binacpp_websocket.cpp
    binacpp_websocket.h
)

set_target_properties(binacpp PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(binacpp PROPERTIES SOVERSION 1)
set_target_properties(binacpp PROPERTIES PUBLIC_HEADER "binacpp.h;binacpp_utils.h")


find_package(CURL)

pkg_check_modules(JSONCPP REQUIRED)
link_libraries(${JSONCPP_LIBRARIES})

pkg_check_modules(WebSockets REQUIRED)
link_libraries(${WebSockets_LIBRARIES})
