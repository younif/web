//
// Created by youni on 2022/6/24.
//

#ifndef WEBSERVER_SOCKETOPS_H
#define WEBSERVER_SOCKETOPS_H


#include <cstdint>

class SocketOps {
public:
    static int createListenSocket(int port);
    static void printEvent(uint32_t event);
};


#endif //WEBSERVER_SOCKETOPS_H
