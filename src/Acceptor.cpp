//
// Created by youni on 2022/6/24.
//

#include <cassert>
#include <unistd.h>
#include "Acceptor.h"
#include "SocketOps.h"
#include "Channel.h"

Acceptor::Acceptor(EventLoop &loop, int port)
    :loop_(loop)
    ,listen_fd_(SocketOps::createListenSocket(port))
    ,isListening_(false)
    ,listenChannel_(std::make_unique<Channel>(loop,listen_fd_))
{

}

Acceptor::~Acceptor() {
    close(listen_fd_);
}

void Acceptor::listen() {
    assert(!isListening_);
    isListening_ = true;
    listenChannel_->enableReading();
}

void Acceptor::handleRead() {

}

bool Acceptor::isListening() {
    return isListening_;
}


