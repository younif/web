//
// Created by youni on 2022/6/24.
//

#include "TcpServer.h"
#include "EventLoop.h"
#include "TcpConnection.h"

void onConnection(std::shared_ptr<TcpConnection>& con){
    con->send("onConnection\n");
    con->enableReading();
}

void onRead(std::shared_ptr<TcpConnection>& con){
    con->send("onRead\n");
    con->disableReading();
    con->enableWriting();
}

void onWrite(std::shared_ptr<TcpConnection>& con){
    con->send("onWrite\n");
    con->disableWriting();
    con->shutdown();
}

int main(){
    EventLoop loop;
    TcpServer server(loop,8800,0);

    server.setConnectionCallback(onConnection);
    server.setReadCallback(onRead);
    server.setWriteCallback(onWrite);

    server.start();
    loop.start();
}