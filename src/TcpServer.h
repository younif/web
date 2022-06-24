//
// Created by youni on 2022/6/24.
//

#ifndef WEBSERVER_TCPSERVER_H
#define WEBSERVER_TCPSERVER_H

#include <functional>
#include <memory>
#include <unordered_map>
#include "Callbacks.h"

class Acceptor;
class EventLoop;
class EventLoopThreadPool;
class TcpConnection;

class TcpServer {

public:
    TcpServer(EventLoop& loop,int port, int threadNum);
    ~TcpServer();
    void start();

    void setConnectionCallback(const ConnectionCallback& cb){connectionCallback_ = cb;};
    void setWriteCallback(const WriteCallback& cb){writeCallback_ = cb;};
    void setReadCallback(const ReadCallback& cb){readCallback_ = cb;};
private:
    void onNewConnection(int fd);

    EventLoop& loop_;
    std::unique_ptr<Acceptor> acceptor_;
    std::shared_ptr<EventLoopThreadPool> threadPool_;

    std::unordered_map<std::string,std::shared_ptr<TcpConnection>> connections_;

    ConnectionCallback connectionCallback_;
    WriteCallback writeCallback_;
    ReadCallback readCallback_;
};


#endif //WEBSERVER_TCPSERVER_H
