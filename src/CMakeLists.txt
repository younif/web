configure_file ("config.h.in" "config.h" )
include_directories(${CMAKE_CURRENT_BINARY_DIR})


set(SRC
        main.cpp
        Acceptor.cpp
        Mutex.h
        EventLoop.cpp
        EventLoopThread.cpp
        EventLoopThreadPool.cpp
        Poller.cpp
        Channel.cpp
        noncopyable.h
        SocketOps.cpp
        TcpServer.cpp
        )

add_executable(server ${SRC})
target_link_libraries(server spdlog)

add_subdirectory(test)