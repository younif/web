//
// Created by youni on 2022/6/24.
//

#ifndef WEBSERVER_CALLBACKS_H
#define WEBSERVER_CALLBACKS_H

#include <functional>
#include <memory>

class TcpConnection;

using ConnectionCallback = std::function<void( const std::shared_ptr<TcpConnection>& con)>;
using WriteCallback = std::function<void(const std::shared_ptr<TcpConnection>& con)>;
using ReadCallback = std::function<void(const std::shared_ptr<TcpConnection>& con)>;
using CloseCallback = std::function<void(const std::shared_ptr<TcpConnection>& con)>;
using NewConnectionCallback = std::function<void(int fd)>;
using ChannelEventCallback = std::function<void ()>;
#endif //WEBSERVER_CALLBACKS_H
