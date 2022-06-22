//
// Created by youni on 2022/6/19.
//

#ifndef WEBSERVER_EVENTLOOP_H
#define WEBSERVER_EVENTLOOP_H

#include "noncopyable.h"
#include <memory>
#include <unistd.h>
#include <atomic>

class Poller;

class EventLoop:noncopyable {

public:
    EventLoop();
    ~EventLoop();
    void start();
    void stop();

    void assertInLoopThread();
    bool isInLoopThread() const;
    static EventLoop* getEventLoopOfCurrentThread();
private:
    void abortNotInLoopThread();

    std::unique_ptr<Poller> poller_;
    pid_t tid_;
    bool looping_;
    std::atomic<bool> request_stop_;
};



#endif //WEBSERVER_EVENTLOOP_H
