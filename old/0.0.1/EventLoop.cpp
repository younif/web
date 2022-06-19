//
// Created by youni on 2022/6/17.
//

#include <unistd.h>
#include "EventLoop.h"
#include "spdlog/spdlog.h"

[[noreturn]] void EventLoop::run() {
    while(true){
        int nums = epoll_wait(epoll_fd_,&epoll_event_list_[0],static_cast<int>(epoll_event_list_.size()),-1);
        SPDLOG_ERROR("connection event nums: " + std::to_string(nums));
        for (int i = 0; i < nums; ++i) {
            auto Connection = static_cast<class Connection*>(epoll_event_list_[i].data.ptr);
            Connection->handleEvent(epoll_event_list_[i].events);
        }
        timer_wheel_index_ = (timer_wheel_index_ + 1) % timer_wheel_.size();
        timer_wheel_[timer_wheel_index_].clear();
    }
}

void EventLoop::add(int fd) {
    timer_wheel_[timer_wheel_index_].insert(timer_wheel_[timer_wheel_index_].begin(), std::make_unique<Connection>(fd, epoll_fd_));
}

EventLoop::EventLoop()
        :epoll_fd_(epoll_create1(EPOLL_CLOEXEC))
        ,timer_wheel_index_(0)
        ,timer_wheel_(5)
        ,epoll_event_list_(5)
{
}

void EventLoop::del(int fd) {
    epoll_ctl(epoll_fd_,EPOLL_CTL_DEL,fd, nullptr);
    ::close(fd);
}




