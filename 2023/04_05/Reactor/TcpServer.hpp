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
  Connection(int sock, TcpServer *r) : _sock(sock), R(r)
  {
  }
  ~Connection()
  {
  }

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

    // 添加 listensock 到epoll中

    Epoller::AddEvent(_epfd, _listensock, EPOLLIN | EPOLLET); // ET模式
    // 这里还是有问题,如果listensock的就绪另外,我们该如何
    Connection *conn = new Connection(_listensock, this);
    conn->SetRecver(std::bind(&TcpServer::Accepter, this, std::placeholders::_1)); // 设置回调方法
    _connections.insert(std::make_pair(_listensock, conn));
  }

  TcpServer()
  {
    if (-1 != _listensock)
      close(_listensock);
    if (-1 != _epfd)
      close(_epfd);
    if (_revs)
      delete[] _revs;
  }

public:
  /// @brief 事件派发
  void Dispatcher()
  {
    int n = Epoller::LoopOnce(_epfd, _revs, revs_num);
    for (int i = 0; i < n; i++)
    {
      int sock = _revs[i].data.fd;
      uint32_t revent = _revs[i].events;
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
      if (revent & EPOLLERR)
      {
        if (IsExists(sock) && _connections[sock]->_excepter)
        {
          _connections[sock]->_excepter(_connections[sock]);
        }
      }
    }
  }

  void Run()
  {
    while (true)
    {
      Dispatcher();
    }
  }

  /// @brief 这个哈函数现在主要是为了 监听套接字获得新连接来的
  /// @param con
  /// @return
  int Accepter(Connection *con)
  {
    std::string clientIp;
    std::uint16_t clientPort;
    int sockFd = Sock::Accept(con->_sock, &clientIp, &clientPort);
    if (sockFd < 0)
    {
      logMessage(WARINING, "获取失败");
      return -1;
    }
    logMessage(DEBUG, "获得 一个新的连接 %d.............", sockFd);
    AddConnection(sockFd, EPOLLIN | EPOLLET); // 这里事件有点问题
    return sockFd;
  }

  void AddConnection(int sockfd, uint32_t event)
  {
    if (event & EPOLLET)
      Util::SetNonBlock(sockfd);

    Epoller::AddEvent(_epfd, sockfd, event);

    Connection *conn = new Connection(sockfd, this);

    conn->SetRecver(std::bind(&TcpServer::TcpRecver, this, std::placeholders::_1));     // 设置回调方法
    conn->SetSender(std::bind(&TcpServer::TcpSender, this, std::placeholders::_1));     // 设置回调方法
    conn->SetExcepter(std::bind(&TcpServer::TcpExcepter, this, std::placeholders::_1)); // 设置回调方法

    _connections.insert(std::make_pair(sockfd, conn));
    logMessage(DEBUG, "添加新连接成功 %d", sockfd);

    // 给新的陶杰设置新的回调方法
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
        logMessage(NOTICE, "退出了");
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
          // 真正的出错
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
    return 0;
  }
  int TcpExcepter(Connection *con)
  {
    return 0;
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
};

