configure_file ("config.h.in" "config.h" )
include_directories(${CMAKE_CURRENT_BINARY_DIR})


set(SRC
        main.cpp
        mutex.h
        EventLoop.cpp)

add_executable(server ${SRC})