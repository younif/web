//
// Created by reads on 2021/10/7.
//
#include "Server.h"
#include "Logger.h"
#include <sys/timerfd.h>
#include <unistd.h>
#include <fcntl.h>

Server::Server(string name, InetAddress localAddr) :
        name_(std::move(name)),
        local_address_(localAddr),
        epoll_fd_(epoll_create1(EPOLL_CLOEXEC)),
        epoll_event_list_(init_epoll_list_size),
        listen_fd_(::socket(local_address_.addr()->sa_family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0)),
        listen_channel_(epoll_fd_, listen_fd_, "listen_channel"),
        timer_fd_(::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC)),
        timer_channel_(epoll_fd_, timer_fd_, "timer_channel"),
        timer_wheel_(init_time_wheel_size),
        timer_wheel_index_(0),
        idle_fd_(open("/dev/null", 0)),
        connection_nums(0) {
    //设置复用端口
    int reuse = 1;
    setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    //设置监听套接字
    if (listen_fd_ == 0) { LOG << "couldn't creat socket"; }
    if (bind(listen_fd_, local_address_.addr(), *local_address_.size())) { LOG << "bind error"; }
    if (listen(listen_fd_, SOMAXCONN)) { LOG << "listen error"; }
    //管理模块间的连接
    listen_channel_.setReadCallback([this] { this->new_connection(); });
    timer_channel_.setReadCallback([this] { this->on_time(); });
    //设置定时器
    itimerspec it{};
    it.it_interval.tv_sec = 1;
    it.it_value.tv_sec = 1;
    timerfd_settime(timer_fd_, 0, &it, nullptr); //处理到期链接

    //LOG << "Server_name:" << name_ << "  IpPort:" << local_address_.toIpPort();
}

[[noreturn]] void Server::run() {
    listen_channel_.enableReading();
    timer_channel_.enableReading();
    while (true) {
        //LOG << name_ << " is waiting for active events";
        int nums = epoll_wait(epoll_fd_, &epoll_event_list_[0], (int) epoll_event_list_.size(), -1);
        //LOG << name_ << " has found active events nums:"  << nums;
        for (int i = 0; i < nums; i++) {
            auto active_event = static_cast<Channel *>(epoll_event_list_[i].data.ptr);

            //查看事件情况
//            cout << "handle " << active_event->name() << " events:";
//            uint32_t events = epoll_event_list_[i].events;
//            if(events & EPOLLIN) cout << "EPOLLIN ";
//            if(events & EPOLLPRI) cout << "EPOLLPRI ";
//            if(events & EPOLLRDHUP) cout << "EPOLLRDHUP ";
//            if(events & EPOLLOUT) cout << "EPOLLOUT ";
//            if(events & EPOLLERR) cout << "EPOLLERR ";
//            if(events & EPOLLHUP) cout << "EPOLLHUP";
//            LOG << "";

            active_event->handleEvent(epoll_event_list_[i].events);
        }
    }
}

void Server::new_connection() {
    while (true) {
        int new_fd = accept4(listen_fd_, nullptr, nullptr, SOCK_NONBLOCK);
        if (new_fd > 0) {
            timer_wheel_[timer_wheel_index_].insert(timer_wheel_[timer_wheel_index_].begin(),
                                                    make_unique<Connection>(new_fd, epoll_fd_));
            connection_nums++;
        } else {
            break;
        }
    }
}

void Server::on_time() {
    uint64_t nums;
    ::read(timer_fd_, &nums, sizeof(nums));
    timer_wheel_index_ = (timer_wheel_index_ + 1) % timer_wheel_.size();
    connection_nums -= timer_wheel_[timer_wheel_index_].size();
    //LOG << "Connection on time nums:" << connection_nums;
    timer_wheel_[timer_wheel_index_] = list<unique_ptr<Connection>>();
}

