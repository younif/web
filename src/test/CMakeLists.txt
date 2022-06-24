add_executable(Poller_UnitTest Poller_UnitTest.cpp ../Poller.cpp)
target_link_libraries(Poller_UnitTest spdlog)

add_executable(EventLoop_UnitTest EventLoop_UnitTest.cpp ../EventLoop.cpp ../Poller.cpp ../Channel.cpp)
target_link_libraries(EventLoop_UnitTest spdlog)

add_executable(Channel_UnitTest Channel_UnitTest.cpp ../Channel.cpp)
target_link_libraries(Channel_UnitTest spdlog)