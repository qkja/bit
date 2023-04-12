#pragma once
#include <iostream>
#include "Log.hpp"
#include <string>
#include <functional>
#include <cstdlib>
#include <sys/epoll.h>
#include "Sock.hpp"

class EpollServer
{
public:
  static const int gszie = 128;
  static const int num = 256;
  using func_t = std::function<int(int)>;

public:
  EpollServer(uint16_t port, func_t func)
      : _listenSock(-1), _port(port), _epfd(-1), _func(func)
  {
  }
  ~EpollServer()
  {
    if (-1 != _listenSock)
      close(_listenSock);
    if (-1 != _epfd)
      close(_epfd);
  }

public:
  void InitEpollServer()
  {
    _listenSock = Sock::Socket();   // 创建监听
    Sock::Bind(_listenSock, _port); // 绑定
    Sock::Listen(_listenSock);      //  监听

    logMessage(DEBUG, "创建监听套接字成功 %d", _listenSock);

    _epfd = epoll_create(gszie); // gszie 随便写

    if (-1 == _epfd)
    {
      logMessage(FATAL, "%d:%s", errno, strerror(errno));
      exit(3);
    }

    logMessage(DEBUG, "创建epoll成功     %d", _epfd);
  }

  void Run()
  {
    // 添加_listenSock到我们的 epoll 模型 -- 添加红黑树
    struct epoll_event ev;
    ev.events = EPOLLIN;      // 常见的事件  课件上面都有
    ev.data.fd = _listenSock; // 这里还没有方法谈,这里弱化一下
    int n = epoll_ctl(_epfd, EPOLL_CTL_ADD, _listenSock, &ev);
    assert(n == 0); // 创建成功, 返回值必须 n 等于0

    struct epoll_event revs[num]; // 收集已经就绪的   numc99 可以的, 不过C语言注意一下
    int timeout = 10000;
    while (true)
    {
      int ret = epoll_wait(_epfd, revs, num, timeout);
      switch (ret)
      {
      case 0:
        std::cout << "time out ... : " << (unsigned long)time(nullptr) << std::endl;
        break;
      case -1:
        std::cerr << "errno " << strerror(errno) << std::endl;
        break;
      default:
        // std::cout << "已经到来" << std::endl;

        HandlerEvents(revs, ret);
        break;
      }
    }
  }

private:
  void HandlerEvents(struct epoll_event revs[], int n)
  {
    // 进的这个数组我们都是合法的
    for (size_t i = 0; i < n; i++)
    {
      int sock = revs[i].data.fd;
      uint32_t revent = revs[i].events;

      if (revent & EPOLLIN) // 这里先判断 是哪一个事件就绪
      {
        // 读时间就绪
        if (sock == _listenSock)
        {
          std::string clientpP;
          std::uint16_t clientPort;
          int s = Sock::Accept(_listenSock, &clientpP, &clientPort);
          // 这里也是需要关注的
          if (s < 0)
          {
            logMessage(WARINING, "%d:%s", errno, strerror(errno));
            continue;
          }

          // 托管给 epoll
          struct epoll_event ev;
          ev.events = EPOLLIN;                     // 常见的事件  课件上面都有
          ev.data.fd = s;                          // 这里还没有方法谈,这里弱化一下
          epoll_ctl(_epfd, EPOLL_CTL_ADD, s, &ev); // 问题,这里我们是不是有点问题,要知道它是局部变量
        }
        else
        {

          int n = _func(sock);
          if (n == 0 || n < 0)
          {
            int x = epoll_ctl(_epfd, EPOLL_CTL_DEL, sock, nullptr);
            close(sock); // 注意,是先移除在关闭

            assert(x == 0);
            logMessage(DEBUG, "client[%d]已经退出", sock);
          }
        }
      }
    }
  }

private:
  int _listenSock;
  int _epfd; // ep模型
  uint16_t _port;
  func_t _func;
};