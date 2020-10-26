cmake_minimum_required (VERSION 3.0.0)
project (engine VERSION 1.0.0 DESCRIPTION "binance description")

include_directories("./")
include_directories("../lib")
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR}/src "*.cpp")

add_executable(engine
    ${SOURCES}
)

target_link_libraries(engine binacpp)
target_link_libraries(engine jsoncpp)
target_link_libraries(engine curl)
target_link_libraries(engine websockets)
target_link_libraries(engine pthread)
