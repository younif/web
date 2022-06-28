//
// Created by youni on 22-6-26.
//

#ifndef CREACTOR_SRC_PROTORPC_RPCSERVER_H_
#define CREACTOR_SRC_PROTORPC_RPCSERVER_H_

#include "EventLoop.h"
#include <google/protobuf/service.h>

class RpcServer {
 public:
  RpcServer(EventLoop& loop, int port);
  void start();
  void registerService(google::protobuf::Service& );
};

#endif //CREACTOR_SRC_PROTORPC_RPCSERVER_H_
