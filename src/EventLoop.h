//
// Created by youni on 2022/6/19.
//

#ifndef WEBSERVER_EVENTLOOP_H
#define WEBSERVER_EVENTLOOP_H

#include "noncopyable.h"
#include <memory>
#include <unistd.h>
#include <atomic>
#include <vector>

class Poller;
class Channel;

class EventLoop:noncopyable {

public:
    EventLoop();
    ~EventLoop();
    void start();  //需在本线程调用
    void stop();   //线程安全

    //更新订阅
    void updateChannel(Channel* c);
    void removeChannel(Channel* c);
    //线程安全设施
    void assertInLoopThread();
    bool isInLoopThread() const;

    static EventLoop* getEventLoopOfCurrentThread();
private:
    void abortNotInLoopThread();

    std::unique_ptr<Poller> poller_;
    std::vector<Channel*> ChannelList_;
    std::vector<Channel*> activeChannelList_;

    pid_t tid_;
    bool looping_;
    std::atomic<bool> request_stop_;
};



#endif //WEBSERVER_EVENTLOOP_H
