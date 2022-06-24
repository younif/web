//
// Created by youni on 2022/6/24.
//

#include "EventLoopThreadPool.h"
#include "EventLoopThread.h"
#include "EventLoop.h"
#include "spdlog/spdlog.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop &loop, int threadNum)
        : loop_(loop)
        , cnt(0)
        ,threadNum_(threadNum)
                                         {
    for (int i = 0; i < threadNum; ++i) {
        EventLoopThread et;
        threadPool_.push_back(et.start());
    }
}

std::unique_ptr<EventLoop>& EventLoopThreadPool::getNextLoop() {
    cnt = ((cnt++) % threadNum_);
    SPDLOG_INFO(std::to_string(cnt));
    return threadPool_[cnt];
}
