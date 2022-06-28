cmake_minimum_required(VERSION 3.16)

project(CReactor)

enable_testing()

set(CMAKE_CXX_STANDARD 20)


#message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

add_subdirectory(src)
add_subdirectory(3rd)
add_subdirectory(example)
add_subdirectory(benchmark)