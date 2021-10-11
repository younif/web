//
// Created by read on 2021/10/8.
//

#include <unistd.h>
#include "Connection.h"
#include "HttpData.h"


Connection::Connection(int fd, int epoll_fd)
: fd_(fd), rcv_index_(0), snd_index_(0){
    getpeername(fd, peerAddr_.addr(), peerAddr_.size());
    channel_ = new Channel(epoll_fd,fd,peerAddr_.toIpPort()+"'s channel");
    channel_->setReadCallback([this]{this->handleRead();});
    channel_->setWriteCallback([this]{ this->handleWrite();});
    channel_->setCloseCallback([this]{ this->handleClose();});
    channel_->enableReading();
    rcv_buf_.resize(50);

    //LOG << "new Connection at:" << peerAddr_.toIpPort();
}

void Connection::handleRead() {
    //LOG << "handleRead at " << peerAddr_.toIpPort();
    auto nums = read(fd_, &rcv_buf_[rcv_index_], sizeof(char) * (rcv_buf_.size() - rcv_index_));
    if(nums <= 0 ) {
        //LOG << "read EOF or error at " << peerAddr_.toIpPort();
        handleClose();
    }
    rcv_index_ += nums;
    if(rcv_index_ == rcv_buf_.size()) rcv_buf_.resize(rcv_index_ * 2);

    // 检查是否读取到末尾，可优化
    auto index = rcv_buf_.find("\r\n\r\n");
    if(index != string::npos){
        rcv_buf_.resize(index);
        request_.push(std::move(rcv_buf_));
        rcv_buf_ = std::move(string (50,' '));
        rcv_index_ = 0;

        channel_->enableWriting();
    }
}

void Connection::handleWrite() {
    if(!request_.empty()){
        //LOG << request_.front() << " at " << peerAddr_.toIpPort();
        HttpData data(request_.front());
        string filename = data.URL();
        string body;
        if(data.isDir()){
            //根据目录构造目录网页
            body = std::move(data.dirBody());
        }else{
            //读取文件
            FILE *fp = ::fopen(&data.URL()[0], "rb");;
            size_t read_len;
            size_t file_index = 0;

            body.resize(100);
            while ((read_len = ::fread(&body[file_index], 1, sizeof(char) * (body.size() - file_index), fp)) > 0) {
                file_index += read_len;
                if(body.size() - file_index == 0) body.resize(file_index + 20);
            }
        }
        //构造返回请求
        snd_buf_ += data.responseHead();
        snd_buf_ += body + "\r\n\r\n";
        request_.pop();
    }

    auto len = send(fd_,&snd_buf_[snd_index_],snd_buf_.size()-snd_index_,0);
    snd_index_ += len;
    if(snd_index_ == snd_buf_.size()){
        //LOG << peerAddr_.toIpPort() << " has snd done!";
        channel_->disableWriting();
    }
}

void Connection::handleClose() {
    //LOG << "close connection:" << peerAddr_.toIpPort();
    delete(channel_);
    channel_ = nullptr;
}

Connection::~Connection() {
    //LOG << "time out close at:" << peerAddr_.toIpPort();
    handleClose();
}































