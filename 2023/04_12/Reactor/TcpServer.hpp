#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "Protocol.hpp"
#include <functional>
#include "Epoller.hpp"
#include <vector>
#include "util.hpp"
#include "Sock.hpp"
#include "Log.hpp"
// 基于Recotor模式,编写一个充分读取和写入的 ET的server
// 基于Recotor模式 --> 这个模式我暂时不谈,写完代码谈
class Connection;
class TcpServer;
using func_t = std::function<int(Connection *)>;
using callback_t = std::function<int(Connection *, std::string &)>;

class Connection
{
public:
  Connection(int sock, TcpServer *r) : _sock(sock), R(r) {}
  ~Connection() {}

public:
  void SetRecver(func_t recver) { _recver = recver; }
  void SetSender(func_t sender) { _sender = sender; }
  void SetExcepter(func_t excepter) { _excepter = excepter; }

public:
  TcpServer *R;
  int _sock;             // 文件描述符
  std::string inbuffer;  // 接受缓冲区
  std::string outbuffer; // 发送缓冲区

  // 回调函数
  func_t _recver;
  func_t _sender;
  func_t _excepter;
};

class TcpServer
{
public:
  TcpServer()
  {
    if (-1 != _listensock)
      close(_listensock);
    if (-1 != _epfd)
      close(_epfd);
    if (_revs)
      delete[] _revs;
  }
  TcpServer(callback_t cb, int port = 8080)
      : _cb(cb)
  {
    _revs = new struct epoll_event[revs_num]; //
    // 网络功能
    _listensock = Sock::Socket();
    Util::SetNonBlock(_listensock);
    Sock::Bind(_listensock, port);
    Sock::Listen(_listensock);

    // 多路转接
    _epfd = Epoller::CreateEpoller();

    AddConnection(_listensock, EPOLLIN | EPOLLET,
                  std::bind(&TcpServer::Accepter, this, std::placeholders::_1), nullptr, nullptr);
  }

public:
  void Run()
  {
    while (true)
    {
      Dispatcher();
    }
  }
  /// @brief 事件派发
  void Dispatcher()
  {
    int n = Epoller::LoopOnce(_epfd, _revs, revs_num);
    for (int i = 0; i < n; i++)
    {
      int sock = _revs[i].data.fd;
      uint32_t revent = _revs[i].events;

      if (revent & EPOLLHUP)
        revent |= (EPOLLIN | EPOLLOUT); // 解释EPOLLHUP是对放关闭了,此时我们加上读事件,在读中一定出现0,然后关闭就可以了
      if (revent & EPOLLERR)
        revent |= (EPOLLIN | EPOLLOUT);

      if (revent & EPOLLIN)
      {
        if (IsExists(sock) && _connections[sock]->_recver) // 假设 这里一定存在这个kv值,
        {
          _connections[sock]->_recver(_connections[sock]);
        }
      }
      // 我们读可能出错,也就是此时我们的kv值可能被消失,所以要判断
      if (revent & EPOLLOUT)
      {
        if (IsExists(sock) && _connections[sock]->_sender)
        {
          _connections[sock]->_sender(_connections[sock]);
        }
      }
    }
  }

  void AddConnection(int sockfd, uint32_t event, func_t recver, func_t sender, func_t excepter)
  {
    if (event & EPOLLET)
      Util::SetNonBlock(sockfd);

    Epoller::AddEvent(_epfd, sockfd, event); // 添加套接字 到 epoll中

    Connection *conn = new Connection(sockfd, this);

    conn->SetRecver(recver);     // 设置回调方法
    conn->SetSender(sender);     // 设置回调方法
    conn->SetExcepter(excepter); // 设置回调方法

    _connections.insert(std::make_pair(sockfd, conn));
    logMessage(DEBUG, "添加新连接成功 %d", sockfd);
  }

  /// @brief 这个函数现在主要是为了 监听套接字获得新连接来的
  /// @param con
  /// @return
  int Accepter(Connection *con)
  {
    // // 这里出现一个问题, 这里也是ET模式，如果我们来了一批连接，此时就只能一次拿到一个，所以要循环读取
    // while (true)
    // {
    //   std::string clientIp;
    //   std::uint16_t clientPort = 0;
    //   int sockFd = Sock::Accept(con->_sock, &clientIp, &clientPort);
    //   if (sockFd < 0)
    //   {
    //     if (errno == EINTR)
    //     {
    //       continue; // 因为信号
    //     }
    //     else if (errno == EAGAIN || errno == EWOULDBLOCK)
    //     {
    //       break; // 这是因为读完出错
    //     }
    //     else
    //     {
    //       logMessage(WARINING, "获取失败");
    //       return -1;
    //     }
    //   }

    //   logMessage(DEBUG, "获得 一个新的连接 %d", sockFd);

    //   AddConnection(sockFd, EPOLLIN | EPOLLET,
    //                 std::bind(&TcpServer::TcpRecver, this, std::placeholders::_1),
    //                 std::bind(&TcpServer::TcpSender, this, std::placeholders::_1),
    //                 std::bind(&TcpServer::TcpExcepter, this, std::placeholders::_1));
    //   logMessage(DEBUG, "绑定成功 %d", sockFd);
    // }

    // 这里出现一个问题, 这里也是ET模式，如果我们来了一批连接，此时就只能一次拿到一个，所以要循环读取
    // 注意,这里暂时我们这样写,我感觉有的地方写错了,回去修改
    // 这里没有错误,开始的时候写空间一定是就绪的
    // 那么运行的时候呢?可能会存在调节不满足,也就是写空间被些慢了
    //
    std::string clientIp;
    std::uint16_t clientPort = 0;
    int sockFd = Sock::Accept(con->_sock, &clientIp, &clientPort);
    if (sockFd < 0)
    {
      logMessage(WARNING, "获取失败");
      return -1;
    }

    logMessage(DEBUG, "获得 一个新的连接 %d", sockFd);

    AddConnection(sockFd, EPOLLIN | EPOLLET,
                  std::bind(&TcpServer::TcpRecver, this, std::placeholders::_1),
                  std::bind(&TcpServer::TcpSender, this, std::placeholders::_1),
                  std::bind(&TcpServer::TcpExcepter, this, std::placeholders::_1));
    logMessage(DEBUG, "绑定成功 %d", sockFd);

    return 0;
  }

  // 给新的陶杰设置新的回调方法
  int TcpRecver(Connection *con)
  {
    char buffer[1024];

    /// 开始正式读取
    while (true)
    {
      buffer[0] = '\0';
      ssize_t s = recv(con->_sock, buffer, sizeof(buffer) - 1, 0);
      if (s > 0)
      {
        buffer[s] = '\0';
        con->inbuffer += buffer;
      }
      else if (0 == s)
      {
        con->_excepter(con);
        logMessage(NOTICE, "退出了");
        break;
      }
      else
      {
        if (errno == EINTR)
        {
          continue; // 因为信号
        }
        else if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
          break; // 这是因为读晚而出错
        }
        else
        {
          con->_excepter(con);
          logMessage(WARNING, "recv失败了");
          break;
        }
      }
    }

    // 报文分割  ,反序列化  -- 供上层使用
    std::vector<std::string> results;
    PackageSplit(con->inbuffer, &results);
    for (auto &message : results)
    {
      _cb(con, message);
    }
    return 0;
  }

  int TcpSender(Connection *con)
  {
    while (true)
    {
      ssize_t n = send(con->_sock, con->outbuffer.c_str(), con->outbuffer.size(), 0);
      if (n > 0)
      {
        // 这里需要清除缓冲区
        con->outbuffer.erase(0, n);
      }
      else
      {
        if (errno == EINTR)
        {
          continue;
        }
        else if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
          break;
        }
        else
        {
          con->_excepter(con);
          logMessage(WARNING, "send失败了");
          break;
        }
      }
    }

    // if (con->outbuffer.empty())
    //   con->R->EnableReadWrite(con->_sock, true, false);
    // else
    //   con->R->EnableReadWrite(con->_sock, true, true);
    return 0;
  }

  /// @brief 异常处理
  /// @param con
  /// @return
  int TcpExcepter(Connection *con)
  {
    // 移除该文件描述地方的挂心
    Epoller::DelEvent(_epfd, con->_sock);
    // 这里存在一个坑,一定是先移除,后面关系
    logMessage(DEBUG, "移除成功 %d", con->_sock);
    close(con->_sock);
    logMessage(DEBUG, "关闭成功 %d", con->_sock);

    // 3.资源管理
    int sock = con->_sock;
    delete _connections[con->_sock];
    _connections.erase(sock); // 这里注意
    return 0;
  }
  void EnableReadWrite(int sock, bool readable, bool writeable)
  {
    uint32_t event = 0;
    event |= (readable ? EPOLLIN : 0);
    event |= (writeable ? EPOLLOUT : 0);
    Epoller::ModEvent(_epfd, sock, event);
  }

private:
  bool IsExists(int sock)
  {
    return _connections.find(sock) != _connections.end();
  }

private:
  static const int revs_num = 64;
  // 1. 网络socket
  int _listensock = -1;
  // 2. epoll
  int _epfd = -1;
  // 3. 将网络和上层代码进行结合
  std::unordered_map<int, Connection *> _connections;

  // 4. 就绪事件列表
  struct epoll_event *_revs = nullptr;
  // 5. 设置啊完整报文的处理方法
  callback_t _cb;

  // 6. 绑定服务
  std::unordered_map<std::string, callback_t> _cbs; // 给服务起名字
};
