//
// Created by youni on 2022/6/24.
//
#include "HttpServer.h"
#include "EventLoop.h"

int main(){
    EventLoop loop;
    HttpServer httpServer(loop,8080,std::filesystem::path(),2);
    httpServer.start();
    loop.start();
}