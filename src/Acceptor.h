//
// Created by youni on 2022/6/24.
//

#ifndef WEBSERVER_ACCEPTOR_H
#define WEBSERVER_ACCEPTOR_H

#include "noncopyable.h"
#include <memory>
class EventLoop;
class Channel;

class Acceptor:noncopyable {
public:
    Acceptor(EventLoop& loop, int port);
    ~Acceptor();

    void listen();
    bool isListening();

private:
    void handleRead();

    EventLoop& loop_;
    bool isListening_;
    int listen_fd_;
    std::unique_ptr<Channel> listenChannel_;
};


#endif //WEBSERVER_ACCEPTOR_H
