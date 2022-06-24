//
// Created by youni on 2022/6/24.
//

#include "TcpConnection.h"
#include "Channel.h"
#include "EventLoop.h"

void TcpConnection::send(const std::string& message) {

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
}

TcpConnection::TcpConnection(EventLoop &loop, int fd)
    :loop_(loop)
    ,channel_(std::make_unique<Channel>(loop,fd))
{

}

TcpConnection::~TcpConnection() {
    shutdown();
}

std::string TcpConnection::name() {
    return std::string();
}
