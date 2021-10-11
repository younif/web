cmake_minimum_required(VERSION 3.16)

project(web )

set(SRC
        main.cpp
        Server.cpp
        InetAddress.cpp
        Channel.cpp
        Connection.cpp
        HttpData.cpp)

add_executable(web ${SRC})
target_link_libraries(web stdc++fs)