//
// Created by youni on 2022/6/24.
//

#ifndef WEBSERVER_TCPSERVER_H
#define WEBSERVER_TCPSERVER_H


#include <memory>

class Acceptor;
class EventLoop;
class EventLoopThreadPool;

class TcpServer {
public:
    TcpServer(EventLoop& loop,int port, int threadNum);
private:
    EventLoop& loop_;
    std::unique_ptr<Acceptor> acceptor_;
    std::shared_ptr<>
};


#endif //WEBSERVER_TCPSERVER_H
