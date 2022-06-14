cmake_minimum_required(VERSION 3.16)

project(WebServer)

add_executable(WebServer main.cpp)

target_link_libraries(WebServer stdc++fs)