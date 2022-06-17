//
// Created by reads on 2021/10/7.
//

#include "Channel.h"
#include <unistd.h>


void Channel::handleEvent(uint32_t events) {
    if (events & (EPOLLHUP | EPOLLRDHUP | EPOLLERR)) {
        //LOG << name_ << " closeCallback_()";
        if (close_callback_) close_callback_();
    }
    if (events & (EPOLLIN | EPOLLPRI)) {
        //LOG << name_ << " readCallback_() " ;
        if (read_callback_) read_callback_();
    }
    if (events & EPOLLOUT) {
        //LOG << name_ << " writeCallback_()";
        if (write_callback_) write_callback_();
    }
}

Channel::Channel(const int epollFd, int fd, string name)
        : epoll_fd_(epollFd), fd_(fd), name_(std::move(name)) {
    epoll_event_.events = 0;
    epoll_event_.data.ptr = this;
    ::epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &epoll_event_);
    //LOG << name_ <<" is created";
}

Channel::~Channel() {
    //LOG << name_ << " is destroyed";
    ::epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd_, &epoll_event_);
    close(fd_);
}



