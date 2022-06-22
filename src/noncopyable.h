//
// Created by youni on 2022/6/22.
//

#ifndef WEBSERVER_NONCOPYABLE_H
#define WEBSERVER_NONCOPYABLE_H

/**
 * 资源类继承，不可拷贝、不可赋值
 */

class noncopyable
{
public:
    noncopyable(const noncopyable&) = delete;
    void operator=(const noncopyable&) = delete;

protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

#endif //WEBSERVER_NONCOPYABLE_H
