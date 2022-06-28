//
// Created by youni on 22-6-26.
//
#include "echo.pb.h"
#include "EventLoop.h"
#include "protorpc/RpcServer.h"

class GreeterServiceImpl final : public Greeter{
 public:
  virtual void SayHello(::google::protobuf::RpcController* controller,
                    const HelloRequest* request,
                    HelloReply* response,
                    ::google::protobuf::Closure* done)
  {
    response->set_message("hello !"  + request->name());
    done->Run();
  }
};

int main(){
  EventLoop loop;
  GreeterServiceImpl greeter;
  RpcServer rpc_server(loop,8080);
  rpc_server.registerService(greeter);
  rpc_server.start();
  loop.start();
}