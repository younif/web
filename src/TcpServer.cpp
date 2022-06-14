//
// Created by youni on 22-6-14.
//

#include "TcpServer.h"
#include "Common.h"
#include <netinet/in.h>

TcpServer::TcpServer(int port)
  :port_(port)
{



}

void TcpServer::setup_listening_socket() {
  int sock;
  struct sockaddr_in srv_addr{};

  sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock == -1)
    fatal_error("socket()");

  int enable = 1;
  if (setsockopt(sock,
                 SOL_SOCKET, SO_REUSEADDR,
                 &enable, sizeof(int)) < 0)
    fatal_error("setsockopt(SO_REUSEADDR)");



  srv_addr.sin_family = AF_INET;
  srv_addr.sin_port = htons(port_);
  srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  /* We bind to a port and turn this socket into a listening
   * socket.
   * */
  if (bind(sock,
           (const struct sockaddr *)&srv_addr,
           sizeof(srv_addr)) < 0)
    fatal_error("bind()");

  if (listen(sock, 10) < 0)
    fatal_error("listen()");

  listener_ = sock;
}