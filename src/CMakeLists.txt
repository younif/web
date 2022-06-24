configure_file ("config.h.in" "config.h" )
include_directories(${CMAKE_CURRENT_BINARY_DIR})


set(SRC
        main.cpp
        Acceptor.cpp
        Callbacks.h
        Mutex.h
        EventLoop.cpp
        EventLoopThread.cpp
        EventLoopThreadPool.cpp
        Poller.cpp
        Channel.cpp
        noncopyable.h
        SocketOps.cpp
        TcpServer.cpp
        TcpConnection.cpp
        HttpServer.cpp
        )

add_library(server ${SRC})
target_link_libraries(server spdlog)

add_subdirectory(test)