//
// Created by youni on 2022/6/17.
//

#ifndef WEBSERVER_SOCKET_H
#define WEBSERVER_SOCKET_H


class Socket {
public:
    static int create_listen_socket(int port) ;
    static int accept_socket(int listen_socket);
};


#endif //WEBSERVER_SOCKET_H
