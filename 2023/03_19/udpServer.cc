/**
 * User: Qkj
 * Description:
 * Date: 2023-03-19
 * Time: 20:09
 */

// int main()
// {
//   struct sockaddr_in a;

//   return 0;
// }

// struct IP
// {
//   uint32_t part1 : 8;
//   uint32_t part2 : 8;
//   uint32_t part3 : 8;
//   uint32_t part4 : 8;
// };

///@brief 服务端
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unordered_map>

class UDPServer
{
public:
  UDPServer(uint16_t port, std::string ip = "")
      : _port(port),
        _ip(ip)
  {
  }

  ~UDPServer() {}

public:
  void init()
  {
    // 1.  创建套接字
    _socketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (_socketFd < 0)
    {
      std::cout << "创建套接字失败 " << strerror(errno) << "socket" << _socketFd << std::endl;
      exit(1);
    }
    std::cout << "创建套接字成功 socket: " << _socketFd << std::endl;

    // 2. 绑定网络信息 包含ip地址 端口号 和 本地或者域间
    struct sockaddr_in local;
    bzero(&local, sizeof local); // 初始化
    local.sin_family = PF_INET;
    local.sin_port = htons(_port);
    local.sin_addr.s_addr = _ip.empty() ? INADDR_ANY : inet_addr(_ip.c_str()); // INADDR_ANY 就是0

    if (bind(_socketFd, (const sockaddr *)&local, sizeof(local)) == -1)
    {
      std::cout << "UDP 套接字bind 失败  " << strerror(errno) << std::endl;
      exit(2);
    }
    std::cout << "UDP 套接字bind 成功" << std::endl;
  }

  // void start()
  // {

  //   while (true)
  //   {
  //     std::cout << "服务器已经启动成功" << std::endl;
  //     sleep(1);
  //   }
  // }
  void start()
  {

    char inbuffer[1024];  // 读去信息
    char outbuffer[1024]; // 发送信息
    while (true)
    {
      memset(inbuffer, '\0', sizeof(inbuffer));
      memset(outbuffer, '\0', sizeof(inbuffer));
      // 正常进行网络读写
      // 谁给我发消息,我们怎么会消息
      // 后面两个参数是输出行参数
      struct sockaddr_in peer;      // 输出型参数
      socklen_t len = sizeof(peer); // 输入输出型参数

      ssize_t s = recvfrom(_socketFd, inbuffer, sizeof(inbuffer) - 1, 0, (struct sockaddr *)&peer, &len);
      if (s > 0)
      {
        inbuffer[s] = 0; // 当做字符串
      }
      else if (s == -1)
      {
        std::cerr << "读取数据失败 " << strerror(errno) << std::endl;
        continue;
      }

      // 读取成功的,除了读取到对方的数据，你还要读取到对方的网络地址[ip:port]
      std::string peerIp = inet_ntoa(peer.sin_addr); // 拿到了对方的IP
      uint16_t peerPort = ntohs(peer.sin_port);      // 拿到了对方的port
      printf("client# [%s:%d]# %s\n", peerIp.c_str(), peerPort, inbuffer);

      checkOnlineUser(peerIp, peerPort, peer); // 如果存在，什么都不做，如果不存在，就添加
      // fflush(stdout);
      for (int i = 0; i < strlen(inbuffer); i++)
      {
        if (isalpha(inbuffer[i]) && islower(inbuffer[i]))
          outbuffer[i] = toupper(inbuffer[i]);
        else
          outbuffer[i] = toupper(inbuffer[i]);
      }
      messageRoute(peerIp, peerPort, inbuffer); // 消息路由
                                                // sendto(_socketFd, outbuffer, strlen(outbuffer), 0, (const sockaddr *)&peer, sizeof(peer));
    }
  }

  void checkOnlineUser(std::string &ip, uint32_t port, struct sockaddr_in &peer)
  {
    std::string key = ip;
    key += ":";
    key += std::to_string(port);
    auto iter = users.find(key);
    if (iter == users.end())
    {
      users.insert({key, peer});
    }
    else
    {
      // iter->first, iter->second->
      // do nothing
    }
  }

  void messageRoute(std::string ip, uint32_t port, std::string info)
  {

    std::string message = "[";
    message += ip;
    message += ":";
    message += std::to_string(port);
    message += "]# ";
    message += info;

    for (auto &user : users)
    {
      sendto(_socketFd, message.c_str(), message.size(), 0, (struct sockaddr *)&(user.second), sizeof(user.second));
    }
  }

private:
  int _socketFd; // fd
  uint16_t _port;
  std::string _ip;
  std::unordered_map<std::string, struct sockaddr_in> users; // 保存在线的信心
};

static void Usage(const std::string proc)
{
  std::cout << "Usage:\n\t" << proc << "  port [ip]  " << std::endl;
}

int main(int argc, char *argv[])
{
  if (argc != 2 && argc != 3)
  {
    Usage(argv[0]);
    exit(3);
  }
  int port = atoi(argv[1]);
  std::string ip;
  if (argc == 3)
  {
    ip = argv[2];
  }

  UDPServer ser(port, ip);
  ser.init();
  ser.start();
  return 0;
}
