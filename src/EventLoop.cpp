//
// Created by youni on 2022/6/19.
//

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "EventLoop.h"
#include "Poller.h"
#include "spdlog/spdlog.h"
#include <memory>



EventLoop::EventLoop()
    :poller_(std::make_unique<Poller>())
{

}
EventLoop::~EventLoop() {

}
void EventLoop::loop() {
    SPDLOG_TRACE("EventLoop::loop()");

}

