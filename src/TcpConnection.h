//
// Created by youni on 2022/6/24.
//

#ifndef WEBSERVER_TCPCONNECTION_H
#define WEBSERVER_TCPCONNECTION_H

#include <string>
#include <memory>
#include "Callbacks.h"

class Channel;
class EventLoop;

class TcpConnection:std::enable_shared_from_this<TcpConnection> {
public:
    TcpConnection(EventLoop& loop, int fd);
    ~TcpConnection();
    std::string name();

    void enableReading();
    void disableReading();
    void enableWriting();
    void disableWriting();

    void setWriteCallback(const WriteCallback& cb){writeCallback_ = cb;};
    void setReadCallback(const ReadCallback& cb){readCallback_ = cb;};

    void shutdown();
    void send(const std::string& message);
    void read(std::string& message);
private:

    void onRead();
    void onWrite();
    EventLoop& loop_;
    int fd_;
    std::unique_ptr<Channel> channel_;

    ReadCallback readCallback_;
    WriteCallback writeCallback_;
};


#endif //WEBSERVER_TCPCONNECTION_H
