//
// Created by youni on 2022/6/24.
//

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "TcpServer.h"
#include "EventLoop.h"
#include "TcpConnection.h"
#include "spdlog/spdlog.h"

void onConnection(const std::shared_ptr<TcpConnection> &con) {
    SPDLOG_DEBUG("onConnection");
    con->send("onConnection\n");
    con->enableReading();
}

void onRead(const std::shared_ptr<TcpConnection> &con) {
    SPDLOG_DEBUG("onRead");
    std::string message;
    message.resize(100);
    con->read(message);
    SPDLOG_DEBUG("read:" + message);
    con->send("onRead\n");
    con->disableReading();
    con->enableWriting();
}

void onWrite(const std::shared_ptr<TcpConnection> &con) {
    SPDLOG_DEBUG("onWrite");
    con->send("onWrite\n");
    con->disableWriting();
    con->shutdown();
}

int main() {
    spdlog::set_level(spdlog::level::trace);
    SPDLOG_DEBUG("TcpServer_UnitTest start");

    EventLoop loop;
    TcpServer server(loop, 8800, 1, std::string());

    server.setConnectionCallback(onConnection);
    server.setReadCallback(onRead);
    server.setWriteCallback(onWrite);

    server.start();
    loop.start();
}
/**
*  tcp客户端：telnet ip port
*/