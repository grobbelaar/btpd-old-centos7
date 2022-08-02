
add_executable(converter main.cpp)
target_link_libraries(converter btpclient)

add_executable(btpc_merge btpc_merge.cpp)
target_link_libraries(btpc_merge btpclient)
