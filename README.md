# 静态高性能服务器
## 本仓库目的
   - 学习异步多线程框架与HTTP协议
## 方法
   - 在性能与复杂度面前倾向于复杂度降低
   - 先使用标准库，没有则使用系统调用
      - 时间：`chrono`
      - 线程：`Thread`
      - 同步：`Mutex`、`condition_variable`、`Atomic`
      - 文件：`filesystem`
      - 网络：系统调用`socket`
   - 模块间采用function/bind而不是虚函数
   - 使用epoll的Reactor多线程框架
## 优化
优化需要熟悉各个层面的实现协议，然后分析相互作用间是否优化空间。
### HTTP1.0主要延时
   1. DNS解析时延（如果没有缓存）-->由URI确定IP与端口号
   2. TCP三次握手连接建立时延   -->使用TCP协议的必须开销
   3. 服务器解析请求报文，回送HTTP响应报文时延。
### HTTP与TCP之间的影响
  1. TCP建立的时延      -- keepalive持久连接
  2. 延迟确认（捎带确认） -- （与请求应答模式不搭配 ）禁止
  3. 慢启动拥塞控制      -- keepalive持久连接
  4. Nagle算法（减少小包）-- 设置TCP_NODELAY，禁止Nagle
  5. TIME_WAIT积累端口耗尽（主动关闭产生） -- 性能测试用，设置reuseaddr

### TODO
- 支持HTTP客户端并发连接
- 支持keepalive持久连接
- 支持管道化连接

## 整体结构
1. 主线程负责监听套接字并分发已连接套接字。
2. 每个线程上有一个epoll负责监听所有的可读、可写、关闭事件
3. Channel实例向epoll注册、设置、取消事件
4. Connection实例持有Channel实例生命期
5. server使用connection类管理套接字：已建立、可读、可写、关闭事件
## 未来
