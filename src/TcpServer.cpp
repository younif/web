//
// Created by youni on 2022/6/24.
//

#include "TcpServer.h"
#include "Acceptor.h"
#include "EventLoopThreadPool.h"
#include "EventLoop.h"
#include "TcpConnection.h"

TcpServer::TcpServer(EventLoop &loop, int port, int threadNum)
    :loop_(loop)
    ,acceptor_(std::make_unique<Acceptor>(loop,port))
    ,threadPool_(std::make_shared<EventLoopThreadPool>(loop,threadNum))
{
    acceptor_->setNewConnectionCallback([this](int fd){ this->onNewConnection(fd);});

}

void TcpServer::start() {
    acceptor_->start();
}

TcpServer::~TcpServer() {

}

void TcpServer::onNewConnection(int fd) {
    loop_.assertInLoopThread();
    auto& ioLoop = threadPool_->getNextLoop();
    auto con = new TcpConnection(ioLoop,fd);
    connections_[con->name()] = std::shared_ptr<TcpConnection>(con);
    con->setReadCallback(readCallback_);
    con->setWriteCallback(writeCallback_);
    connectionCallback_(connections_[con->name()]);
}
