set(SRC
        HttpServer.cpp
        HttpServer.h
        TcpServer.cpp
        TcpServer.h
        EventLoop.cpp
        EventLoop.h
        Common.cpp
        Common.h
        )

add_library(server ${SRC})