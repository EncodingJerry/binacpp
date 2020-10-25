cmake_minimum_required (VERSION 2.8.11)
project (BinaceTrader)

find_package(CURL 7.69.1 REQUIRED)
# rpm -sq cppzmq-devel
find_package(cppzmq)

find_library(JSONCPP NAMES libjsoncpp.so.1.9.2)
find_library(WebSockets NAMES libwebsockets.so.15)
find_library(ZMQ NAMES libzmq.so.5.2.3)

if(NOT JSONCPP)
  message(FATAL_ERROR "jsoncpp library not found")
endif()

if(NOT WebSockets)
  message(FATAL_ERROR "websockets library libwebsockets not found")
endif()

if(NOT ZMQ)
  message(FATAL_ERROR "ZMQ library libzmq not found")
endif()

add_subdirectory (src)
add_subdirectory (example)
