//
// Created by youni on 2022/6/22.
//

#include "Poller.h"
#include <sys/epoll.h>
#include <unistd.h>

Poller::Poller()
    :epoll_fd_(epoll_create1(EPOLL_CLOEXEC))
{

}

Poller::~Poller() {
    ::close(epoll_fd_);
}

std::chrono::system_clock::time_point
Poller::poll(std::chrono::system_clock::duration duration, std::vector<Channel> &channelList) {
    return std::chrono::system_clock::time_point();
}

