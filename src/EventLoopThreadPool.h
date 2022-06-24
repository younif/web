//
// Created by youni on 2022/6/24.
//

#ifndef WEBSERVER_EVENTLOOPTHREADPOOL_H
#define WEBSERVER_EVENTLOOPTHREADPOOL_H

#include <vector>
#include <memory>
#include <functional>
class EventLoop;


class EventLoopThreadPool {
public:
    EventLoopThreadPool(EventLoop& loop, int threadNum);
    EventLoop& getNextLoop();

private:
    int cnt;
    int threadNum_;
    EventLoop& loop_;
    std::vector<std::unique_ptr<EventLoop>> threadPool_;
};


#endif //WEBSERVER_EVENTLOOPTHREADPOOL_H
