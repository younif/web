//
// Created by youni on 2022/6/22.
//
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "../EventLoop.h"
#include "spdlog/spdlog.h"
#include <thread>

int main(){
    spdlog::set_level(spdlog::level::trace);

    EventLoop loop;
    SPDLOG_TRACE("loop in thread");
    std::thread thread([&](){loop.loop();});
    thread.join();
}