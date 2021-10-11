//
// Created by 王鸿鑫 on 2021/9/4.
//

#include <cstring>
#include "InetAddress.h"
#include <arpa/inet.h>
#include <vector>

InetAddress::InetAddress(const uint16_t port, const std::string &ip) {
    bzero(&addr_, sizeof(sockaddr_in));
    size_ = sizeof(sockaddr_in);
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    ip.empty() ? addr_.sin_addr.s_addr = INADDR_ANY : inet_pton(AF_INET, ip.c_str(), &addr_.sin_addr.s_addr);
}

std::string InetAddress::toIp() const {
    std::vector<char> buff(addr_.sin_family == AF_INET ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN);
    ::inet_ntop(addr_.sin_family, &addr_.sin_addr, &buff[0], buff.size());
    return buff.data();
}

int InetAddress::toPort() const {
    return ntohs(addr_.sin_port);
}

std::string InetAddress::toIpPort() const {
    return toIp() + "-" + std::to_string(toPort());
}


