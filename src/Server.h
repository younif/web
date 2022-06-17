//
// Created by reads on 2021/10/7.
//

#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <string>
#include <vector>
#include <memory>
#include "EventLoop.h"


class EventLoop;

class Server {
public:
    Server(std::string name, int port, std::string root, int threads, std::string log_path);
    [[noreturn]] void run();
private:
    const std::string name_;
    int idle_fd_;
    int listen_fd_;
    std::vector<std::unique_ptr<EventLoop>> workers;
};


#endif //WEB_SERVER_H
