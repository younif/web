//
// Created by read on 2021/10/8.
//

#include <unistd.h>
#include "Connection.h"
#include "HttpData.h"
#include "spdlog/spdlog.h"




Connection::Connection(int fd, int epoll_fd)
        : fd_(fd), rcv_index_(0), snd_index_(0),epoll_fd_(epoll_fd) {
    getpeername(fd, peerAddr_.addr(), peerAddr_.size());
    event_.data.ptr = this;
    event_.events = EPOLLIN | EPOLLPRI;
    epoll_ctl(epoll_fd,EPOLL_CTL_ADD,fd,&event_);
    rcv_buf_.resize(1000);
}

void Connection::handleRead() {
    //SPDLOG_ERROR("handleRead at " + peerAddr_.toIpPort());
    auto nums = read(fd_, &rcv_buf_[rcv_index_], sizeof(char) * (rcv_buf_.size() - rcv_index_));
    if (nums <= 0) {
        //LOG << "read EOF or error at " << peerAddr_.toIpPort();
        handleClose();
    }
    rcv_index_ += nums;
    if (rcv_index_ == rcv_buf_.size()) rcv_buf_.resize(rcv_index_ * 2);

    // 检查是否读取到末尾，可优化
    auto index = rcv_buf_.find("\r\n\r\n");
    if (index != string::npos) {
        //SPDLOG_ERROR("rcv_buf:" + rcv_buf_);
        rcv_buf_.resize(index);
        request_.push(std::move(rcv_buf_));
        rcv_buf_ = std::move(string(1000, ' '));
        rcv_index_ = 0;
        event_.events |= EPOLLOUT;
        epoll_ctl(epoll_fd_,EPOLL_CTL_MOD,fd_,&event_);
    }
}

void Connection::handleWrite() {
    SPDLOG_ERROR("handleWrite at " + peerAddr_.toIpPort());
    if (!request_.empty()) {
        //LOG << request_.front() << " at " << peerAddr_.toIpPort();
        HttpData data(request_.front());
        string filename = data.URL();
        string body;
        if (data.isDir()) {
            //根据目录构造目录网页
            body = std::move(data.dirBody());
        } else {
            //读取文件
            FILE *fp = ::fopen(&data.URL()[0], "rb");;
            size_t read_len;
            size_t file_index = 0;

            body.resize(100);
            while ((read_len = ::fread(&body[file_index], 1, sizeof(char) * (body.size() - file_index), fp)) > 0) {
                file_index += read_len;
                if (body.size() - file_index == 0) body.resize(file_index + 20);
            }
        }
        //构造返回请求
        snd_buf_ += data.responseHead();
        SPDLOG_ERROR(snd_buf_);
        snd_buf_ += body + "\r\n\r\n";
        request_.pop();
    }

    auto len = send(fd_, &snd_buf_[snd_index_], snd_buf_.size() - snd_index_, 0);
    snd_index_ += len;
    if (snd_index_ == snd_buf_.size()) {
        //LOG << peerAddr_.toIpPort() << " has snd done!";
        event_.events &= ~EPOLLOUT;
        epoll_ctl(epoll_fd_,EPOLL_CTL_MOD,fd_,&event_);
    }
}

void Connection::handleClose() {
    epoll_ctl(epoll_fd_,EPOLL_CTL_DEL,fd_, nullptr);
    close(fd_);
}

Connection::~Connection() {

    handleClose();
}

void Connection::handleEvent(uint32_t events) {
    SPDLOG_ERROR("------------------");
    if(events & EPOLLIN) SPDLOG_ERROR("EPOLLIN");
    if(events & EPOLLPRI) SPDLOG_ERROR("EPOLLPRI");
    if(events & EPOLLRDHUP) SPDLOG_ERROR("EPOLLRDHUP");
    if(events & EPOLLOUT) SPDLOG_ERROR("EPOLLOUT");
    if(events & EPOLLERR) SPDLOG_ERROR("EPOLLERR");
    if(events & EPOLLHUP) SPDLOG_ERROR("EPOLLHUP");
    SPDLOG_ERROR("^^^^^^^^^^^^^^^^^^");
    if (events & (EPOLLHUP | EPOLLRDHUP | EPOLLERR)) {
        handleClose();
    }
    if (events & (EPOLLIN | EPOLLPRI)) {
        handleRead();
    }
    if (events & EPOLLOUT) {
        handleWrite();
    }
}































