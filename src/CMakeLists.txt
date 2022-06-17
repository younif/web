configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/config.h" )

set(SRC
        main.cpp
        Server.cpp
        InetAddress.cpp
        Channel.cpp
        Connection.cpp
        HttpData.cpp)

add_executable(web ${SRC})
target_link_libraries(web stdc++fs)

add_subdirectory(test)