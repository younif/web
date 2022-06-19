configure_file ("config.h.in" "config.h" )

set(SRC
        main.cpp
        Server.cpp
        InetAddress.cpp
        Connection.cpp
        HttpData.cpp
        Socket.cpp
        EventLoop.cpp
        )

add_executable(web ${SRC})
target_link_libraries(web stdc++fs spdlog)

add_subdirectory(test)