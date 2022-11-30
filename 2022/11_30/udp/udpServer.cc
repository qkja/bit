/**
 * Author       : Qkj
 * Description  : udp套接字
 * Date         : 2022-11-27 10:39:59
 * LastEditTime : 2022-11-27 10:43:20
 */
// 域间套接字  -- 一个主机内通信
// 在当时 C语言还是不支持void*的,一般一要是看一本书,和你的观点不一样,这里
// 你就要测试一下,可能书有些陈旧
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Log.hpp"
// 这是一个服务器
class UdpServer
{
public:
  UdpServer(int port = 0, std::string ip = "")
      : _sockfd(-1), _port((uint16_t)port), _ip(ip)
  {}
  ~UdpServer()
  {}

public:
  void init()
  {
    _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (_sockfd < 0)
    {
      logMessage(FATAL, "%s:%d", strerror(errno), _sockfd);
      exit(1);
    }
    logMessage(DEBUG, "socket create success: %d", _sockfd);

    struct sockaddr_in local;
    // 初始化
    bzero(&local, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(_port); // 本机转网络
    // IP地址是一个4 字节的IP地址 我们需要转化
    // Linux给我们做好了
    local.sin_addr.s_addr = _ip.empty() ? htonl(INADDR_ANY) : inet_addr(_ip.c_str());
    // 注意你的端口号呀不要发给对方?ip呢?
    // 2.2 绑定
    if (bind(_sockfd, (const struct sockaddr *)&local, sizeof(local)) == -1)
    {
      logMessage(FATAL, "%s:%d", strerror(errno), _sockfd);
      exit(2);
    }
    // 对于udp服务器到这里就完成了  此时我们需要接受任务
    logMessage(DEBUG, "socket bind success: %d", _sockfd);
    // done
  }

  void start()
  {
    char inBuffer[1024];  // 读取的数据
    char outBuffer[1024]; // 发送的数据
    while (true)
    {
      struct sockaddr_in peer;
      socklen_t len = sizeof(peer);
      bzero(&peer, len);
      ssize_t s = recvfrom(_sockfd, inBuffer, sizeof(inBuffer) - 1, 0, (struct sockaddr *)&peer, &len);
      sleep(1);
    }
    // while (true)
    // {
    //   logMessage(NOTICE, "server 提供服务中");
    //   sleep(1);
    // }
  }

private:
  int _sockfd;
  uint16_t _port;
  std::string _ip;
};

void Usage(const char *proc)
{
  std::cout << "Usage:\n\t" << proc << " port [ip]" << std::endl;
}

int main(int argc, char *argv[])
{
  if (!(argc == 2 || argc == 3))
  {
    Usage(argv[0]);
    exit(3);
  }
  // std::cout << "111111" << std::endl;

  int port = atoi(argv[1]);
  std::string ip;
  if (argc == 3)
    ip = argv[2];
  // std::cout << "111111" << std::endl;

  UdpServer svr(port, ip);
  svr.init();
  sleep(3);
  svr.start();
  return 0;
}
