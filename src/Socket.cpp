//
// Created by youni on 2022/6/17.
//

#include "Socket.h"
#include "Logger.h"
#include "InetAddress.h"
#include <sys/socket.h>

int Socket::create_listen_socket(int port) {
    InetAddress local_addr(port);
    int fd = ::socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);

    //设置复用端口
    int reuse = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    if (fd == 0) { LOG << "couldn't creat Socket"; }
    if (bind(fd, local_addr.addr(), *local_addr.size())) { LOG << "bind error"; }
    if (listen(fd, SOMAXCONN)) { LOG << "listen error"; }
}
