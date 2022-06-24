//
// Created by youni on 2022/6/24.
//

#ifndef WEBSERVER_HTTPSERVER_H
#define WEBSERVER_HTTPSERVER_H


#include <memory>
#include <filesystem>

class TcpServer;
class EventLoop;

class HttpServer {
public:
    HttpServer(EventLoop& loop, int port, std::filesystem::path path, int threadNum);
    void start();
private:
    std::unique_ptr<TcpServer> tcpServer_;
};


#endif //WEBSERVER_HTTPSERVER_H
