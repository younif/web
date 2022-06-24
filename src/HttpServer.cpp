//
// Created by youni on 2022/6/24.
//

#include "HttpServer.h"

HttpServer::HttpServer(EventLoop& loop, int port, std::filesystem::path path, int threadNum)
    :tcpServer_(std::make_unique<TcpServer>(loop, port, threadNum))
{

}

void HttpServer::start() {

}
