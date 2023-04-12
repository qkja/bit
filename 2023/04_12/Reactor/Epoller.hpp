#pragma once
#include <sys/epoll.h>

#include "Log.hpp"

class Epoller
{
public:
  static const int gszie = 128;

public:
  // 创建 句柄
  static int CreateEpoller()
  {
    int epfd = epoll_create(gszie); // gszie 随便写
    if (-1 == epfd)
    {
      logMessage(FATAL, "CreateEpoller() : %d : %s", errno, strerror(errno));
      exit(3);
    }
    return epfd;
  }
  // 移除文件描述符的关心
  static bool DelEvent(int epfd, int sock)
  {
    int n = epoll_ctl(epfd, EPOLL_CTL_DEL, sock, nullptr);
    return n == 0;
  }
  // 添加文件描述符到 epfd中
  static bool AddEvent(int epfd, int sock, uint32_t event)
  {
    struct epoll_event ev;
    ev.events = event;
    ev.data.fd = sock;
    int n = epoll_ctl(epfd, EPOLL_CTL_ADD, sock, &ev);
    return n == 0;
  }

  // 拿到就绪事件
  static int LoopOnce(int epfd, struct epoll_event revs[], int num)
  {
    int n = epoll_wait(epfd, revs, num, -1); // 阻塞式
    if (-1 == n)
    {
      logMessage(FATAL, "epoll_wait %d %s", errno, strerror(errno));
    }
    return n;
  }
  /// @brief 修改epoll模型
  /// @param epfd
  /// @param sock
  /// @param event
  /// @return
  static bool ModEvent(int epfd, int sock, uint32_t event)
  {
    struct epoll_event ev;
    ev.events = event;
    ev.data.fd = sock;

    int n = epoll_ctl(epfd, EPOLL_CTL_MOD, sock, &ev);
    return n == 0;
  }
};