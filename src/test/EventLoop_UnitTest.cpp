//
// Created by youni on 2022/6/22.
//
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "EventLoop.h"
#include "spdlog/spdlog.h"
#include <memory>
#include <thread>
#include <iostream>
#include <unistd.h>


void ThreadFuc(std::unique_ptr<EventLoop> &p) {
    p = std::make_unique<EventLoop>();
    p->start();
}

int main() {
    spdlog::set_level(spdlog::level::trace);
    SPDLOG_TRACE("main() pid:" + std::to_string(getpid()) + " tid:" + std::to_string(gettid()));


    // test for terminating when create another Eventloop in this thread.
    //EventLoop loop;
    //EventLoop loop2;



    //test for not run loop in another thread
//    std::unique_ptr<EventLoop> p;
//    std::thread thread([&](){ ThreadFuc(p);});
//    while(!p);
//    p->assertInLoopThread(); //terminate for not in the thread.
//    thread.join();

    // test for getEventLoopOfCurrentThread
    assert(EventLoop::getEventLoopOfCurrentThread() == nullptr);
    EventLoop loop2;
    assert(EventLoop::getEventLoopOfCurrentThread() == &loop2);

}