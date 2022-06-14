//
// Created by youni on 22-6-14.
//

#ifndef WEBSERVER_SRC_TCPSERVER_H_
#define WEBSERVER_SRC_TCPSERVER_H_

class TcpServer {

  explicit TcpServer(int port);

  void setup_listening_socket();

 private:
  int listener_;
  int port_;
};

#endif //WEBSERVER_SRC_TCPSERVER_H_
