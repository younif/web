//
// Created by youni on 2022/6/24.
//

#ifndef WEBSERVER_ACCEPTOR_H
#define WEBSERVER_ACCEPTOR_H

#include "noncopyable.h"
#include "Callbacks.h"
#include <memory>
class EventLoop;
class Channel;

class Acceptor:noncopyable {
public:
    Acceptor(EventLoop& loop, int port);
    ~Acceptor();

    void start();
    bool isListening();

    void setNewConnectionCallback(const NewConnectionCallback& cb){ newConnectionCallback_ = cb;}

private:
    void handleRead();

    EventLoop& loop_;
    bool isListening_;
    int listen_fd_;
    std::unique_ptr<Channel> listenChannel_;
    NewConnectionCallback newConnectionCallback_;
};


#endif //WEBSERVER_ACCEPTOR_H
