//
// Created by read on 2021/10/8.
//

#ifndef WEB_CONNECTION_H
#define WEB_CONNECTION_H

#include "InetAddress.h"
#include <queue>
#include <thread>
#include <sys/epoll.h>

class Connection {
public:
    Connection(int fd, int epoll_fd);

    ~Connection();

    void handleRead();

    void handleWrite();

    void handleClose();

    void handleEvent(uint32_t events);
private:
    int fd_;
    int epoll_fd_;
    epoll_event event_;
    InetAddress peerAddr_;



    std::string rcv_buf_;
    std::string::size_type rcv_index_;

    std::queue<std::string> request_;
    std::string snd_buf_;
    std::string::size_type snd_index_;
};


#endif //WEB_CONNECTION_H
