//
// Created by 王鸿鑫 on 2021/9/4.
//

#ifndef REACTOR_INETADDRESS_H
#define REACTOR_INETADDRESS_H


#include <netinet/in.h>
#include <string>

class InetAddress {
public:
    explicit InetAddress(uint16_t port = 0, const std::string &ip = std::string());

    sockaddr *addr() { return reinterpret_cast<sockaddr *>(&addr_); }
    socklen_t *size() { return &size_; }

    int toPort() const;
    std::string toIp() const;
    std::string toIpPort() const;

private:
    socklen_t size_;
    sockaddr_in addr_;
};


#endif //REACTOR_INETADDRESS_H
