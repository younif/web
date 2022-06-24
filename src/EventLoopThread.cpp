//
// Created by youni on 2022/6/24.
//

#include "EventLoopThread.h"
#include "EventLoop.h"
#include <cassert>
#include <thread>

EventLoopThread::EventLoopThread()
    :started_(false)
    ,loop_(nullptr)
{

}

std::unique_ptr<EventLoop> EventLoopThread::start() {
    assert(!started_);
    std::thread t([this](){this->startFunc();});
    t.detach();
    {
        std::unique_lock<std::mutex> lock(mutex_);
        con_.wait(lock,[this]{return loop_ != nullptr;});
        started_ = true;
    }
    return std::unique_ptr<EventLoop>(loop_);
}

void EventLoopThread::startFunc() {
    loop_ = new EventLoop();
    con_.notify_one();
    loop_->start();
}
