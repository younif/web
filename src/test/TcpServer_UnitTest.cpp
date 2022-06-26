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
    con->send("Hello world ! - onConnection()\n");
    con->enableReading();
    con->send("We have enabled to read your message now !\nplease input your message:");
}

void onRead(const std::shared_ptr<TcpConnection> &con) {
    SPDLOG_DEBUG("onRead()");
    std::string message;
    message.resize(100);
    con->read(message);
    SPDLOG_DEBUG("We received :" + message );
    con->send("We received :" + message);
    con->disableReading();
    con->enableWriting();
}

void onWrite(const std::shared_ptr<TcpConnection> &con) {
    SPDLOG_DEBUG("onWrite()");
    con->send("Goodbye ! We will Close connection now\n");
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