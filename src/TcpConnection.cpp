//
// Created by youni on 2022/6/24.
//

#include <sys/socket.h>
#include "TcpConnection.h"
#include "Channel.h"
#include "EventLoop.h"

void TcpConnection::send(const std::string& message) {
    ::write(fd_,message.data(),message.length());
}

void TcpConnection::enableReading() {
    channel_->enableReading();
}

void TcpConnection::disableReading() {
    channel_->disableReading();
}

void TcpConnection::enableWriting() {
    channel_->enableWriting();
}

void TcpConnection::disableWriting() {
    channel_->disableWriting();
}

void TcpConnection::shutdown() {
    loop_.removeChannel(*channel_);
    ::shutdown(fd_,SHUT_RDWR);
}

TcpConnection::TcpConnection(EventLoop &loop, int fd)
    :loop_(loop)
    ,fd_(fd)
    ,channel_(std::make_unique<Channel>(loop,fd))
{
    channel_->setReadCallback([&]{onRead();});
    channel_->setWriteCallback([&]{onWrite();});
}

TcpConnection::~TcpConnection() {
    shutdown();
}

std::string TcpConnection::name() {
    return {"tcp connection"};
}

void TcpConnection::read(std::string &message) const {
    auto cnt = ::read(fd_,message.data(),message.length());
    if(cnt != message.length()){
        message.resize(cnt);
    }else{
        message.resize(cnt * 2);
    }
}

void TcpConnection::onRead() {
    readCallback_(shared_from_this());
}

void TcpConnection::onWrite() {
    writeCallback_(shared_from_this());
}
