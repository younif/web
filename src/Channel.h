//
// Created by youni on 2022/6/22.
//

#ifndef WEBSERVER_CHANNEL_H
#define WEBSERVER_CHANNEL_H

#include <sys/epoll.h>
#include <functional>
#include "Callbacks.h"

class EventLoop;

class Channel {

public:
    explicit Channel(EventLoop &loop, int fd);
    ~Channel();
    void handleEvent();
    [[nodiscard]] uint32_t getEvent() const{return event_;}
    [[nodiscard]] int getFd() const {return fd_;}
    void setRevent(uint32_t event){ r_event_ = event;}
    void setReadCallback(const ChannelEventCallback &cb){readCallback_ = cb;}
    void setWriteCallback(const ChannelEventCallback &cb){writeCallback_ = cb;}
    void setErrorCallback(const ChannelEventCallback &cb){errorCallback_ = cb;}
    void enableReading(){ event_ |= EPOLLIN; update();}
    void disableReading(){ event_ &= ~EPOLLIN; update();}
    void enableWriting(){ event_ |= EPOLLOUT; update();}
    void disableWriting(){ event_ &= ~EPOLLOUT; update();}

private:
    static ChannelEventCallback DEFAULT_CALLBACK;
    void update();
    void defaultCallback(){};
    EventLoop& loop_;
    int fd_;
    uint32_t event_;
    uint32_t r_event_;
    ChannelEventCallback readCallback_;
    ChannelEventCallback writeCallback_;
    ChannelEventCallback errorCallback_;
};


#endif //WEBSERVER_CHANNEL_H
