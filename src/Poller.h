//
// Created by youni on 2022/6/22.
//

#ifndef WEBSERVER_POLLER_H
#define WEBSERVER_POLLER_H

#include <sys/epoll.h>

/**
 * 多路复用的抽象
 * 目前用epoll先实现，后面使用继承
 */



class Poller {
public:
    Poller();
    ~Poller();

    void add(int fd);
    void del(int fd);
    void mod(int fd);

    void poll();
private:
    int epoll_fd_;
};


#endif //WEBSERVER_POLLER_H
