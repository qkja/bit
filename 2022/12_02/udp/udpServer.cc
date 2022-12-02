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
#include <unordered_map>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Log.hpp"
// 这是一个服务器
class UdpServer
{
public:
  UdpServer(int port = 0, std::string ip = "")
      : _sockfd(-1), _port((uint16_t)port), _ip(ip)
  {
  }
  ~UdpServer()
  {
  }

public:
  void init()
  {
    // 参数 网络/本机  面向数据报 默认是0
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
      memset(inBuffer, '\0', sizeof(inBuffer));
      ssize_t s = recvfrom(_sockfd, inBuffer, sizeof(inBuffer) - 1, 0, (struct sockaddr *)&peer, &len);
      if (s > 0)
      {
        inBuffer[s] = '\0';
      }
      else if (-1 == s)
      {
        logMessage(WARING, "读取出错");
        continue;
      }
      // 我们需要对方的数据和网络地址
      // logMessage(NOTICE, "读取成功# ");

      // 客户端ip
      std::string peerIp = inet_ntoa(peer.sin_addr);
      // 客户端端口
      uint16_t peerPort = ntohs(peer.sin_port);

      // 检查 如果存在什么都不做
      checkOnlineUser(std::string& ip, uint16_t port)
      {
        _user[]
      }





      logMessage(NOTICE, "[%s : %d]# %s", peerIp.c_str(), peerPort, inBuffer);
      // 现在我已经收到消息,我想把消息在发回去 -- 给所有人
      // 退一步 -- 协会去大小写转化
      for (size_t i = 0; i < s; i++)
      {
        if (isalpha(inBuffer[i]) && islower(inBuffer[i]))
          outBuffer[i] = toupper(inBuffer[i]);
        else
          outBuffer[i] = inBuffer[i];
      }

      // 我想给谁发
      sendto(_sockfd, outBuffer, sizeof(outBuffer), 0,
             (struct sockaddr *)&peer, len);

      memset(outBuffer, '\0', sizeof(outBuffer));
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

  // 路由
  std::unordered_map<std::string, struct sockaddr_in> _users;
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
