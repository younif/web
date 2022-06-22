//
// Created by youni on 2022/6/19.
//

#ifndef WEBSERVER_EVENTLOOP_H
#define WEBSERVER_EVENTLOOP_H

#include <memory>

class Poller;

class EventLoop {
public:
    EventLoop();
    ~EventLoop();
    void loop();
private:
    std::unique_ptr<Poller> poller_;
};


#endif //WEBSERVER_EVENTLOOP_H
