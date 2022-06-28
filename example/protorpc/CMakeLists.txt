add_custom_command(OUTPUT echo.pb.cc echo.pb.h
        COMMAND protoc
        ARGS --cpp_out . echo.proto -I${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS echo.proto)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(echo_proto echo.pb.cc)
target_link_libraries(echo_proto protobuf pthread)

add_executable(protobuf_rpc_echo_client client.cpp)
set_target_properties(protobuf_rpc_echo_client PROPERTIES COMPILE_FLAGS "-Wno-error=shadow")
target_link_libraries(protobuf_rpc_echo_client echo_proto CReactor)

add_executable(protobuf_rpc_echo_server server.cpp)
set_target_properties(protobuf_rpc_echo_server PROPERTIES COMPILE_FLAGS "-Wno-error=shadow")
target_link_libraries(protobuf_rpc_echo_server echo_proto CReactor)