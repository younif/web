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
#include <memory>
#include <sys/epoll.h>
#include "noncopyable.h"

class Channel;
using Timepoint = std::chrono::system_clock::time_point;
using Duration = std::chrono::milliseconds;



class Poller:noncopyable {
public:
    Poller();
    ~Poller();
    Timepoint poll(Duration duration, std::vector<Channel*> &channelList);
    void add(const Channel &c);
    void mod(const Channel &c);
    void del(const Channel &c);
private:
    static void channelToEpollEvent(const Channel &c, epoll_event* e);
    int epoll_fd_;
    std::vector<epoll_event> eventList_;
};


#endif //WEBSERVER_POLLER_H
