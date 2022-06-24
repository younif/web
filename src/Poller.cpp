//
// Created by youni on 2022/6/22.
//



#include "Poller.h"
#include "Channel.h"
#include "SocketOps.h"
#include <spdlog/spdlog.h>
#include <sys/epoll.h>
#include <unistd.h>

Poller::Poller()
    :epoll_fd_(epoll_create1(EPOLL_CLOEXEC))
    ,eventList_(1)
{
    SPDLOG_INFO("Poller created - fd:" + std::to_string(epoll_fd_));
}

Poller::~Poller() {
    ::close(epoll_fd_);
}

std::chrono::system_clock::time_point
Poller::poll(Duration duration, std::vector<Channel*> &channelList) {
    auto event_num = epoll_wait(epoll_fd_,eventList_.data(),static_cast<int>(eventList_.size()),static_cast<int>(duration.count()));
    //SPDLOG_INFO("Poller::poll() - get:" + std::to_string(event_num) + " at epoll:" + std::to_string(epoll_fd_));
    auto ret = std::chrono::system_clock::now();
    if(event_num > 0){
        for (int i = 0; i < event_num; ++i) {
            auto c = static_cast<Channel*>(eventList_[i].data.ptr);
            c->setRevent(eventList_[i].events);
            channelList.push_back(c);
        }
        if(event_num == eventList_.size()){
            eventList_.resize(event_num * 2);  //二倍放大
        }
    }else if (event_num == 0){
        SPDLOG_INFO("Poller::poll() - nothing happened");
    }else{
        SPDLOG_ERROR("Poller::poll() - epoll_wait error");
    }
    return ret;
}

void Poller::add(const Channel &c) {
    SPDLOG_INFO("Poller::add fd:" + std::to_string(c.getFd()));
    epoll_event e{};
    channelToEpollEvent(c,&e);
    epoll_ctl(epoll_fd_,EPOLL_CTL_ADD,c.getFd(),&e);
}

void Poller::mod(const Channel &c) {
    SPDLOG_INFO("Poller::mod fd:" + std::to_string(c.getFd()));
    epoll_event e{};
    channelToEpollEvent(c,&e);
    //SocketOps::printEvent(e.events);
    epoll_ctl(epoll_fd_,EPOLL_CTL_MOD,c.getFd(),&e);
}

void Poller::del(const Channel &c) {
    SPDLOG_INFO("Poller::del fd:" + std::to_string(c.getFd()));
    epoll_ctl(epoll_fd_,EPOLL_CTL_DEL,c.getFd(), nullptr);
}

void Poller::channelToEpollEvent(const Channel &c, epoll_event *e) {
    auto p = const_cast<Channel*>(&c);
    e->data.ptr = static_cast<void*>(p);
    e->events = c.getEvent();
}

