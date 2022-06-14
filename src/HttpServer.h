//
// Created by youni on 22-6-14.
//

#ifndef WEBSERVER_SRC_HTTPSERVER_H_
#define WEBSERVER_SRC_HTTPSERVER_H_

#include "TcpServer.h"
#include <string>
#include <memory>


class HttpServer {
 public:
  HttpServer(int port, std::string root);
  void run();

 private:
  std::unique_ptr<TcpServer> tcp_server_;
};

#endif //WEBSERVER_SRC_HTTPSERVER_H_
