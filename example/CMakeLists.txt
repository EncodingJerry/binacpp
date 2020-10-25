cmake_minimum_required (VERSION 3.0.0)


include_directories (../src)
set(exampleBins example_aggTrades example example_depthCache example_klines example_template example_userStream example_wapi)
foreach(binName ${exampleBins})
    add_executable(${binName} ${binName}.cpp)

    target_link_libraries(${binName} binacpp)
    target_link_libraries(${binName} jsoncpp)
    target_link_libraries(${binName} curl)
    target_link_libraries(${binName} websockets)
endforeach()
