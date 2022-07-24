add_custom_command(OUTPUT addressbook.pb.cc addressbook.pb.h
        COMMAND protoc
        ARGS --cpp_out . addressbook.proto -I${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS addressbook.proto)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(addressbook_proto addressbook.pb.cc)
target_link_libraries(addressbook_proto protobuf pthread)

add_executable(protobuf_addressbook_client client.cpp)
set_target_properties(protobuf_addressbook_client PROPERTIES COMPILE_FLAGS "-Wno-error=shadow")
target_link_libraries(protobuf_addressbook_client echo_proto CReactor spdlog)

add_executable(protobuf_addressbook_server server.cpp Codec.cpp Dispatcher.cpp)
set_target_properties(protobuf_addressbook_server PROPERTIES COMPILE_FLAGS "-Wno-error=shadow")
target_link_libraries(protobuf_addressbook_server echo_proto CReactor spdlog)