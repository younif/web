//
// Created by youni on 2022/6/17.
//

#ifndef WEBSERVER_EVENTLOOP_H
#define WEBSERVER_EVENTLOOP_H

#include <vector>
#include <memory>
#include <list>
#include "Connection.h"


class EventLoop {
public:
    EventLoop();
    [[noreturn]] void run();
    void add(int fd);
private:
    void del(int fd);
    const int epoll_fd_;
    std::vector<epoll_event> epoll_event_list_;

    std::vector<std::list<std::unique_ptr<Connection>>> timer_wheel_;
    std::vector<std::list<std::unique_ptr<Connection>>>::size_type timer_wheel_index_;
};


#endif //WEBSERVER_EVENTLOOP_H
