//
// Created by youni on 2022/6/19.
//

#include "spdlog/spdlog.h"

#include "EventLoop.h"
#include "Poller.h"
#include "Channel.h"
#include <memory>
#include <thread>
#include <sstream>
#include "spdlog/spdlog.h"


thread_local EventLoop* t_eventLoop = nullptr;

EventLoop::EventLoop()
    :poller_(std::make_unique<Poller>())
    ,tid_(gettid())
    ,looping_(false)
    ,request_stop_(false)
{
    if(t_eventLoop != nullptr){
        SPDLOG_CRITICAL("EventLoop::EventLoop() - already have a EventLoop in this thread!");
        std::exit(-1);
    }else{
        t_eventLoop = this;
    }
    SPDLOG_INFO("EventLoop Created");
}
EventLoop::~EventLoop() {

}
void EventLoop::start() {
    assert(!looping_);   //防止loop中调用loop
    assertInLoopThread();//防止其他线程调用本线程EventLoop
    looping_ = true;
    request_stop_ = false;
    while(!request_stop_){
        activeChannelList_.clear();
        poller_->poll(Duration (-1),activeChannelList_);
        SPDLOG_INFO("get event nums:" + std::to_string(activeChannelList_.size()));
        for(auto c :activeChannelList_){
            c->handleEvent();
        }
    }
}
void EventLoop::stop() {
    request_stop_ = true;
}
void EventLoop::abortNotInLoopThread() {
    std::stringstream s;
    s << "EventLoop::abortNotInLoopThread - run in tid[" << gettid() << "] but create in tid[" << tid_ << "]";
    SPDLOG_CRITICAL(s.str());
    std::exit(-1);
}

void EventLoop::assertInLoopThread() {
    if (!isInLoopThread())
    {
        abortNotInLoopThread();
    }
}

bool EventLoop::isInLoopThread() const {
   return tid_ == gettid();
}

EventLoop *EventLoop::getEventLoopOfCurrentThread() {
    return t_eventLoop;
}

void EventLoop::updateChannel(const Channel &c) {
    poller_->mod(c);
}

void EventLoop::removeChannel(const Channel &c) {
    poller_->del(c);
}

void EventLoop::addChannel(const Channel &c) {
    poller_->add(c);
}



