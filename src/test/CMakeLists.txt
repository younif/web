include_directories(../)

add_executable(Poller_UnitTest Poller_UnitTest.cpp)
target_link_libraries(Poller_UnitTest CReactor spdlog)

add_executable(EventLoop_UnitTest EventLoop_UnitTest.cpp)
target_link_libraries(EventLoop_UnitTest CReactor spdlog)

add_executable(Channel_UnitTest Channel_UnitTest.cpp)
target_link_libraries(Channel_UnitTest CReactor spdlog)

add_executable(TcpServer_UnitTest TcpServer_UnitTest.cpp)
target_link_libraries(TcpServer_UnitTest CReactor spdlog)

add_executable(HttpServer_UnitTest HttpServer_UnitTest.cpp)
target_link_libraries(HttpServer_UnitTest CReactor spdlog)