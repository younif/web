//
// Created by youni on 2022/6/22.
//

#ifndef WEBSERVER_POLLER_H
#define WEBSERVER_POLLER_H

/**
 * 多路复用的抽象
 * 目前用epoll先实现，后面使用继承
 */

#include <chrono>
#include <vector>
#include <sys/epoll.h>
#include "noncopyable.h"

class Channel;
using Timepoint = std::chrono::system_clock::time_point;
using Duration = std::chrono::milliseconds;



class Poller:noncopyable {
public:
    Poller();
    ~Poller();
    Timepoint poll(Duration duration, std::vector<Channel *> &channelList);
    void add(Channel* c);
    void mod(Channel* c);
    void del(Channel* c);
private:
    void channelToEpollEvent(Channel* c, epoll_event* e);
    int epoll_fd_;
    std::vector<epoll_event> eventList_;
};


#endif //WEBSERVER_POLLER_H
