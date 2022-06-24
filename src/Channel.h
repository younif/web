//
// Created by youni on 2022/6/22.
//

#ifndef WEBSERVER_CHANNEL_H
#define WEBSERVER_CHANNEL_H

#include <sys/epoll.h>
#include <functional>

class EventLoop;

class Channel {
    typedef std::function<void ()> EventCallback;
public:
    explicit Channel(EventLoop& loop);
    ~Channel();
    void handleEvent();
    [[nodiscard]] uint32_t getEvent() const{return event_;}
    [[nodiscard]] int getFd() const {return fd_;}
    void setRevent(uint32_t event){ r_event_ = event;}
    void setReadCallback(const EventCallback& cb){readCallback_ = cb;}
    void setWriteCallback(const EventCallback& cb){writeCallback_ = cb;}
    void setErrorCallback(const EventCallback& cb){errorCallback_ = cb;}
    void enableReading(){ event_ |= EPOLLIN; update();}
    void disableReading(){ event_ &= ~EPOLLIN; update();}
    void enableWriting(){ event_ |= EPOLLOUT; update();}
    void disableWriting(){ event_ &= ~EPOLLOUT; update();}

private:
    void update();
    EventLoop& loop_;
    int fd_;
    uint32_t event_;
    uint32_t r_event_;
    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
};


#endif //WEBSERVER_CHANNEL_H
