//
// Created by youni on 2022/6/24.
//

#include "TcpServer.h"
#include "Acceptor.h"
#include "EventLoopThreadPool.h"
#include "EventLoop.h"
#include "TcpConnection.h"
#include "spdlog/spdlog.h"

TcpServer::TcpServer(EventLoop &loop, int port, int threadNum, const std::string &name)
    : loop_(loop)
    , name_(name)
    , acceptor_(std::make_unique<Acceptor>(loop,port))
    , threadPool_(std::make_shared<EventLoopThreadPool>(loop,threadNum))
{
    acceptor_->setNewConnectionCallback([this](int fd){ this->onNewConnection(fd);});
    SPDLOG_TRACE("TcpServer created");
}

void TcpServer::start() {
    acceptor_->start();
}

TcpServer::~TcpServer() {

}

void TcpServer::onNewConnection(int fd) {
    loop_.assertInLoopThread();
    auto& ioLoop = threadPool_->getNextLoop();
    auto con = std::make_shared<TcpConnection>(*ioLoop,fd);
    connections_[con->name()] = con;
    con->setReadCallback(readCallback_);
    con->setWriteCallback(writeCallback_);
    con->setCloseCallback([&](const std::shared_ptr<TcpConnection>& con){ delConnection(con);});
    connectionCallback_(connections_[con->name()]);
}
void TcpServer::delConnection(const std::shared_ptr<TcpConnection>& con) {
    connections_[con->name()].reset();
}
