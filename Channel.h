//
// Created by reads on 2021/10/7.
//

#ifndef WEB_CHANNEL_H
#define WEB_CHANNEL_H

#include "Logger.h"
#include <functional>
#include <utility>
#include <sys/epoll.h>


class Channel {
public:
    typedef std::function<void()> EventCallback;
    //一个文件描述符上可以关心的事件
    void setReadCallback(EventCallback cb){ read_callback_ = std::move(cb); }
    void setWriteCallback(EventCallback cb){ write_callback_ = std::move(cb); }
    void setCloseCallback(EventCallback cb){ close_callback_ = std::move(cb); }

    //subscribe events to epoll
    void enableReading() {
        //LOG << name_ << " has enableReading";
        epoll_event_.events |= EPOLLIN | EPOLLPRI;
        ::epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd_, &epoll_event_);
    }
    void disableReading() {
        LOG << name_ << " has disableReading";
        epoll_event_.events &= ~(EPOLLIN | EPOLLPRI);
        ::epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd_, &epoll_event_);
    }
    void enableWriting() {
        epoll_event_.events |= EPOLLOUT;
        ::epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd_, &epoll_event_);
    }
    void disableWriting() {
        epoll_event_.events &= ~EPOLLOUT;
        ::epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd_, &epoll_event_);
    }
    //由loop根据发生的事件回调设置的各个函数
    void handleEvent(uint32_t events);


    explicit Channel(int epollFd, int fd, string name = "def channel");
    ~Channel();
    string name(){return name_;}
private:
    string name_;
    const int fd_;
    const int epoll_fd_;
    epoll_event epoll_event_{};

    EventCallback read_callback_;
    EventCallback write_callback_;
    EventCallback close_callback_;
};



#endif //WEB_CHANNEL_H
