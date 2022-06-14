cmake_minimum_required(VERSION 3.16)

project(WebServer)


add_subdirectory(src)
include_directories(src)

add_executable(WebServer main.cpp)


target_link_libraries(WebServer server stdc++fs)

add_executable(test test.cpp)
target_link_libraries(test uring)