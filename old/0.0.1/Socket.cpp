//
// Created by youni on 2022/6/17.
//

#include "Socket.h"

#include "InetAddress.h"
#include <sys/socket.h>
#include "spdlog/spdlog.h"

int Socket::create_listen_socket(int port) {
    InetAddress local_addr(port);
    int fd = ::socket(PF_INET, SOCK_STREAM | SOCK_CLOEXEC, 0);

    //设置复用端口
    int reuse = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    if (fd == 0) { SPDLOG_ERROR("couldn't creat Socket"); }
    if (bind(fd, local_addr.addr(), *local_addr.size())) { SPDLOG_ERROR("bind error"); }
    if (listen(fd, SOMAXCONN)) { SPDLOG_ERROR("listen error"); }
    return fd;
}

int Socket::accept_socket(int listen_socket) {
    int fd = accept4(listen_socket, nullptr, nullptr, 0);
    if(fd < 0){
        SPDLOG_ERROR("accept error");
    }else{
        return fd;
    }
}
