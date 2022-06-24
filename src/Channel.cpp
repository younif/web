//
// Created by youni on 2022/6/22.
//

#include "Channel.h"
#include "EventLoop.h"
#include <spdlog/spdlog.h>

ChannelEventCallback Channel::DEFAULT_CALLBACK = {[]{}};

void Channel::handleEvent() {
    if (r_event_ & (EPOLLHUP | EPOLLRDHUP | EPOLLERR)) {
        errorCallback_();
    }
    if (r_event_ & (EPOLLIN | EPOLLPRI)) {
        readCallback_();
    }
    if (r_event_ & EPOLLOUT) {
        writeCallback_();
    }
}

void Channel::update() {
    loop_.updateChannel(*this);
}

Channel::Channel(EventLoop &loop, int fd)
    :loop_(loop)
    ,fd_(fd)
    ,readCallback_(DEFAULT_CALLBACK)
    ,writeCallback_(DEFAULT_CALLBACK)
    ,errorCallback_(DEFAULT_CALLBACK)
    ,event_(0)
    ,r_event_(0)
{
    loop_.addChannel(*this);
}

Channel::~Channel() {
    loop_.removeChannel(*this);
}


