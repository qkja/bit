#pragma once
#include <string>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

#include <poll.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/socket.h>

class Sock
{
public:
  static const int gbacklog = 20; // 全连接队列的长度
  static int Socket()
  {
    // 1. 创建socket
    int listenSock = socket(PF_INET, SOCK_STREAM, 0);
    if (listenSock < 0)
    {
      exit(-1);
    }
    int opt = 1;
    setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof opt); // 服务器崩掉了,我们可以立马重启
    return listenSock;
  }

  static void Bind(int listenSock, std::uint16_t port)
  {
    struct sockaddr_in local;
    memset(&local, 0, sizeof local);
    local.sin_family = PF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = INADDR_ANY;

    if (bind(listenSock, (const struct sockaddr *)&local, sizeof local) < 0)
    {
      exit(-2);
    }
  }

  static void Listen(int listenSock)
  {
    if (listen(listenSock, gbacklog) < 0)
    {
      exit(-3);
    }
  }
  
  static int Accept(int listenSock, std::string *clientIP, std::uint16_t *clientPort)
  {
    struct sockaddr_in peer;
    socklen_t len = sizeof(peer);
    int serviceSock = accept(listenSock, (struct sockaddr *)&peer, &len);
    if (serviceSock < 0)
    {
      exit(-4);
    }
    if (clientPort)
      *clientPort = ntohs(peer.sin_port);
    if (clientIP)
      *clientIP = inet_ntoa(peer.sin_addr);
    return serviceSock;
  }
};
