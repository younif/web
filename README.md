#静态高性能服务器
1. 原则
   1. 为了学习基本且重要的原理，避免细枝末节的优化而导致代码的复杂
   2. 尽可能的采用标准库里的实现
      1. 时间采用：`chrono`程序库
      2. 多线程采用`Thread`程序库
      3. 同步使用`Mutex`与`condition_variable`工具
      4. 原子使用`Atomic`函数库
      5. 读取目录中的文件使用`filesystem`
   3. 在性能与复杂度面前倾向于复杂度降低

2. 特点
   1. 仅支持 IPV4
   2. 关于网络方面没有标准库的实现，则使用系统调用接口
   3. 仅使用epoll 的Reactor 框架
   4. 支持多线程
   5. 支持HTTP客户端并发连接
   6. 支持keepalive持久连接
   7. 支持管道化连接
   8. 实现GET方法
   9. 模块之间的连接采用function/lambda/bind
   
3. HTTP服务网络时延的主要构成
   1. 由URI确定IP与端口号的DNS解析时延（如果没有缓存）
   2. TCP三次握手连接建立时延
   3. 服务器解析请求报文，回送HTTP响应报文时延。

4. HTTP与TCP之间的影响
   1. TCP
      1. TCP建立的时延      -- keepalive持久连接
      2. 延迟确认（捎带确认） -- （与请求应答模式不搭配 ）禁止
      3. 慢启动拥塞控制      -- keepalive持久连接
      4. Nagle算法（减少小包）-- 设置TCP_NODELAY，禁止Nagle
      5. TIME_WAIT积累端口耗尽（主动关闭产生） -- 性能测试用，设置reuseaddr
   2. HTTP
5. 整体结构
   1. Server的epoll作为整体的驱动力负责监听文件描述符上的可读、可写、关闭事件
   2. Channel与epoll进行配合，Channel向epoll注册、设置、取消事件
   3. Channel由Connection持有其生命期