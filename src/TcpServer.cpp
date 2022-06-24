//
// Created by youni on 2022/6/24.
//

#include "TcpServer.h"
#include "Acceptor.h"

TcpServer::TcpServer(EventLoop &loop, int port, int threadNum)
    :loop_(loop)
    ,acceptor_(std::make_unique<Acceptor>(loop,port))
{

}
