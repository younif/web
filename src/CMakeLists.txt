configure_file ("config.h.in" "config.h" )
include_directories(${CMAKE_CURRENT_BINARY_DIR})


set(SRC
        main.cpp
        mutex.h
        EventLoop.cpp
        Poller.cpp
        Channel.cpp)

add_executable(server ${SRC})
target_link_libraries(server spdlog)

add_subdirectory(test)