# A C++ HTTP Server

## feature
- 采用function/bind代替虚函数作为接口
- 使用epoll的Reactor多线程框架

## 整体结构

1. 仅主线程负责监听套接字并分发已连接套接字到工作线程，避免群惊。
2. 每个线程使用epoll负责其所有套接字的可读、可写、关闭事件
3. Channel实例向epoll注册、设置、取消事件
4. Connection实例持有Channel实例生命期，管理：已建立、可读、可写、关闭事件
5. httpServer实例持有connection类

## 性能分析与测试


## 未来

- 可选HTTP/3中的QUIC协议替代TCP协议。
- 高并发长链接下使用io_uring替代epoll，减少系统调用开销