//
// Created by youni on 2022/6/22.
//

#include "Channel.h"
#include "EventLoop.h"
#include <spdlog/spdlog.h>

void Channel::handleEvent() {
//    SPDLOG_ERROR("------------------");
//    if(event_ & EPOLLIN) SPDLOG_ERROR("EPOLLIN");
//    if(event_ & EPOLLPRI) SPDLOG_ERROR("EPOLLPRI");
//    if(event_ & EPOLLRDHUP) SPDLOG_ERROR("EPOLLRDHUP");
//    if(event_ & EPOLLOUT) SPDLOG_ERROR("EPOLLOUT");
//    if(event_ & EPOLLERR) SPDLOG_ERROR("EPOLLERR");
//    if(event_ & EPOLLHUP) SPDLOG_ERROR("EPOLLHUP");
//    SPDLOG_ERROR("^^^^^^^^^^^^^^^^^^");
    if (event_ & (EPOLLHUP | EPOLLRDHUP | EPOLLERR)) {
        errorCallback_();
    }
    if (event_ & (EPOLLIN | EPOLLPRI)) {
        readCallback_();
    }
    if (event_ & EPOLLOUT) {
        writeCallback_();
    }
}

void Channel::update() {
    loop_.updateChannel(this);
}

Channel::Channel(EventLoop &loop)
    :loop_(loop)
{

}

Channel::~Channel() {
    loop_.removeChannel(this);
}


