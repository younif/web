//
// Created by youni on 2022/6/24.
//

#include "SocketOps.h"
#include "spdlog/spdlog.h"
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>

int SocketOps::createListenSocket(int port) {
    int sock;
    struct sockaddr_in srv_addr{};

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        SPDLOG_CRITICAL("socket()");

    int enable = 1;
    if (setsockopt(sock,
                   SOL_SOCKET, SO_REUSEADDR,
                   &enable, sizeof(int)) < 0)
        SPDLOG_CRITICAL("setsockopt(SO_REUSEADDR)");


    memset(&srv_addr, 0, sizeof(srv_addr));
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(port);
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock,
             (const struct sockaddr *)&srv_addr,
             sizeof(srv_addr)) < 0)
        SPDLOG_CRITICAL("bind()");

    if (listen(sock, 10) < 0)
        SPDLOG_CRITICAL("listen()");

    return (sock);
}

void SocketOps::printEvent(uint32_t event) {
    SPDLOG_INFO("----printEvent------");
    if(event & EPOLLIN) SPDLOG_INFO("EPOLLIN");
    if(event & EPOLLPRI) SPDLOG_INFO("EPOLLPRI");
    if(event & EPOLLRDHUP) SPDLOG_INFO("EPOLLRDHUP");
    if(event & EPOLLOUT) SPDLOG_INFO("EPOLLOUT");
    if(event & EPOLLERR) SPDLOG_INFO("EPOLLERR");
    if(event & EPOLLHUP) SPDLOG_INFO("EPOLLHUP");
    SPDLOG_INFO("^^^^printEvent^^^^^^");
}
