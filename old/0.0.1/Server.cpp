//
// Created by reads on 2021/10/7.
//
#include "Server.h"

#include "Socket.h"
#include "EventLoop.h"
#include <fcntl.h>
#include <memory>
#include <thread>

using std::string;
using std::thread;
using std::unique_ptr;
using std::make_unique;


Server::Server(string name, int port, string root, int threads, string log_path)
    :name_(std::move(name)),
    listen_fd_(0),
    idle_fd_(open("/dev/null", 0))
{
    listen_fd_ = Socket::create_listen_socket(port);
    for(int i = 0; i < threads; i++){
        workers.emplace_back(new EventLoop);
        thread t([this]{this->workers.back()->run();});
        t.detach();
    }
}

[[noreturn]] void Server::run() {
    auto it = workers.begin();
    while (true) {
        for(auto & w : workers){
            int new_fd = Socket::accept_socket(listen_fd_);
            w->add(new_fd);
        }
    }
}



