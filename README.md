# A C++20 HTTP Server

## 本仓库目的

- 学习异步多线程框架与HTTP协议

## 方法

- 在性能与代码复杂度中，选择复杂度降低
- 先使用标准库，没有则使用系统调用
    - 时间：`chrono`
    - 线程：`Thread`
    - 同步：`Mutex`、`condition_variable`、`Atomic`
    - 文件：`filesystem`
    - 网络：系统调用`socket`
- 模块间采用function/bind而不是虚函数
- 使用epoll的Reactor多线程框架

## 优化

优化需要熟悉各个层面的实现协议，然后分析相互作用间是否优化空间，针对主要时延进行优化。

### HTTP1.0主要延时

1. DNS解析时延（如果没有缓存）-->由URI确定IP与端口号
2. TCP三次握手连接建立时延 -->使用TCP协议的必须开销
3. 服务器接收请求并响应报文时延

### TCP对HTTP的影响与应对策略

1. TCP建立的时延--keepalive持久连接，减少建立次数
2. 慢启动拥塞控制--keepalive持久连接，避开建立时的慢启动
3. Nagle算法 --设置TCP_NODELAY（HTTP请求应答模式不搭配 ）
4. TIME_WAIT积累端口耗尽（服务端主动关闭） -- 性能测试用，设置reuseaddr
5. TCP队头堵塞 --弱网环境下（丢包率高），堵塞会严重

### 零拷贝

零拷贝优化是指数据在硬盘、用户态内存、内核态内存、网卡之间的数据拷贝优化，主要是基于内存映射来减少拷贝。

#### sendfile

#### mmap

## 注意

多线程避免伪共享--CacheLine大小内的读写引起的缓存失效

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