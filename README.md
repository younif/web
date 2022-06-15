# 静态高性能服务器
## 本仓库目的
   - 学习异步多线程框架
   - 学习HTTP协议
## 方法
   - 在性能与复杂度面前倾向于复杂度降低
   - 先使用标准库，没有则使用系统调用
      - 时间：`chrono`
      - 线程：`Thread`
      - 同步：`Mutex`、`condition_variable`、`Atomic`
      - 文件：`filesystem`
      - 网络：系统调用`socket`
   - 模块连接采用function/bind而不是虚函数
   - 使用epoll的Reactor多线程框架
## 优化
优化需要对各个层面的实现机制熟悉，然后分析各层之间的相互作用是否优化空间。
### HTTP全流程


   1. 由URI确定IP与端口号的DNS解析时延（如果没有缓存）
   2. TCP三次握手连接建立时延
   3. 服务器解析请求报文，回送HTTP响应报文时延。
### HTTP与TCP之间的影响
   1. TCP
      1. TCP建立的时延      -- keepalive持久连接
      2. 延迟确认（捎带确认） -- （与请求应答模式不搭配 ）禁止
      3. 慢启动拥塞控制      -- keepalive持久连接
      4. Nagle算法（减少小包）-- 设置TCP_NODELAY，禁止Nagle
      5. TIME_WAIT积累端口耗尽（主动关闭产生） -- 性能测试用，设置reuseaddr
### 缓存

### TODO
- 支持HTTP客户端并发连接
- 支持keepalive持久连接
- 支持管道化连接

## 整体结构
   1. Server的epoll作为整体的驱动力负责监听文件描述符上的可读、可写、关闭事件
   2. Channel与epoll进行配合，Channel向epoll注册、设置、取消事件
   3. Channel由Connection持有其生命期

## 未来
