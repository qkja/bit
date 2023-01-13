#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <pthread.h>
#include "log.hpp"
class Task
{
private:
  // typedef std::function<void(int, std::string, uint16_t)> callback_t;
  using callback_t = std::function<void(int, std::string, uint16_t)>;

public:
  Task(int sock, std::string ip, uint16_t port, callback_t func)
      : _sock(sock), _ip(ip), _port(port), _func(func)
  {
  }
  Task()
      : _sock(-1), _port(0)

  {
  }
  ~Task()
  {
  }
  int run()
  {
    logMessage(DEBUG, "线程id %p 处理%s %d 的请求开始了...", pthread_self(), _ip.c_str(), _port);
    _func(_sock, _ip, _port);// 回调函数
    logMessage(DEBUG, "线程id %p 处理%s %d 的请求结束了...", pthread_self(), _ip.c_str(), _port);
  }

  int operator()()
  {
    return run();
  }

private:
  int _sock;
  std::string _ip;
  uint16_t _port;
  callback_t _func; // 回调方法
};