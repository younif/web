//
// Created by read on 2021/10/8.
//

#ifndef WEB_CONNECTION_H
#define WEB_CONNECTION_H


#include "Channel.h"
#include "InetAddress.h"
#include <queue>

class Connection {
public:
    Connection(int fd, int epoll_fd);

    ~Connection();

    void handleRead();

    void handleWrite();

    void handleClose();

private:
    int fd_;
    InetAddress peerAddr_;
    Channel *channel_;

    string rcv_buf_;
    string::size_type rcv_index_;

    queue<string> request_;
    string snd_buf_;
    string::size_type snd_index_;
};


#endif //WEB_CONNECTION_H
