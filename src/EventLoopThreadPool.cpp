//
// Created by youni on 2022/6/24.
//

#include "EventLoopThreadPool.h"
#include "EventLoopThread.h"
#include "EventLoop.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop &loop, int threadNum)
        : loop_(loop)
        , cnt(0)
                                         {
    for (int i = 0; i < threadNum; ++i) {
        EventLoopThread et;
        threadPool_.push_back(et.start());
    }
}

EventLoop& EventLoopThreadPool::getNextLoop() {
    return *threadPool_[(cnt++) % threadNum_];
}
