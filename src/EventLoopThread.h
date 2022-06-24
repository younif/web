//
// Created by youni on 2022/6/24.
//

#ifndef WEBSERVER_EVENTLOOPTHREAD_H
#define WEBSERVER_EVENTLOOPTHREAD_H

#include <memory>
#include <condition_variable>
#include "mutex.h"

class EventLoop;

class EventLoopThread {
public:
    EventLoopThread();
    std::unique_ptr<EventLoop> start();
private:
    void startFunc();
    bool started_ GUARDED_BY(mutex_);
    EventLoop* loop_;
    std::mutex mutex_;
    std::condition_variable con_ GUARDED_BY(mutex_);
};


#endif //WEBSERVER_EVENTLOOPTHREAD_H
