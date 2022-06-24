//
// Created by youni on 2022/6/22.
//

#include "Poller.h"
#include "Channel.h"
#include <spdlog/spdlog.h>
#include <sys/epoll.h>
#include <unistd.h>

Poller::Poller()
    :epoll_fd_(epoll_create1(EPOLL_CLOEXEC))
    ,eventList_(1)
{

}

Poller::~Poller() {
    ::close(epoll_fd_);
}

std::chrono::system_clock::time_point
Poller::poll(Duration duration, std::vector<Channel *> &channelList) {
    auto event_num = epoll_wait(epoll_fd_,eventList_.data(),static_cast<int>(eventList_.size()),static_cast<int>(duration.count()));
    auto ret = std::chrono::system_clock::now();
    if(event_num > 0){
        for (int i = 0; i < event_num; ++i) {
            auto* c = static_cast<Channel *>(eventList_[i].data.ptr);
            c->setRevent(eventList_[i].events);
            channelList.push_back(c);
        }
        if(event_num == eventList_.size()){
            eventList_.resize(event_num * 2);  //二倍放大
        }
    }else if (event_num == 0){
        SPDLOG_TRACE("Poller::poll() - nothing happened");
    }else{
        SPDLOG_ERROR("Poller::poll() - epoll_wait error");
    }
    return ret;
}

void Poller::add(Channel *c) {
    epoll_event e{};
    channelToEpollEvent(c,&e);
    epoll_ctl(epoll_fd_,EPOLL_CTL_ADD,c->getFd(),&e);
}

void Poller::mod(Channel *c) {
    epoll_event e{};
    channelToEpollEvent(c,&e);
    epoll_ctl(epoll_fd_,EPOLL_CTL_MOD,c->getFd(),&e);
}

void Poller::del(Channel *c) {
    epoll_ctl(epoll_fd_,EPOLL_CTL_DEL,c->getFd(), nullptr);
}

void Poller::channelToEpollEvent(Channel *c, epoll_event *e) {
    e->data.ptr = c;
    e->events = c->getEvent();
}

