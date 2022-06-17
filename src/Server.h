//
// Created by reads on 2021/10/7.
//

#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <string>
#include <vector>
#include <list>
#include <memory>
#include <sys/epoll.h>
#include "InetAddress.h"
#include "Channel.h"
#include "Connection.h"


using namespace std;

const int max_connection = 2000;
const int init_epoll_list_size = 1000;
const int init_time_wheel_size = 10;


class Server {
public:
    Server(string name, InetAddress localAddr);

    [[noreturn]] void run();

private:
    const string name_;

    int idle_fd_;
    list<unique_ptr<Connection>>::size_type connection_nums;

    //socket
    InetAddress local_address_;
    const int epoll_fd_;
    int listen_fd_;
    Channel listen_channel_;

    //time
    int timer_fd_;
    Channel timer_channel_;
    vector<list<unique_ptr<Connection>>> timer_wheel_;
    vector<list<unique_ptr<Connection>>>::size_type timer_wheel_index_;

    vector<epoll_event> epoll_event_list_;

    void new_connection();

    void on_time();
};


#endif //WEB_SERVER_H
