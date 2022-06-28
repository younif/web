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
        http/HttpServer.cpp
        )

add_library(CReactor ${SRC})
target_link_libraries(CReactor spdlog)

add_subdirectory(test)

add_executable(main main.cpp)