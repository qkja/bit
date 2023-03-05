/**
 * User: Qkj
 * Description:
 * Date: 2023-03-05
 * Time: 14:28
 */

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <unordered_map>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Log.hpp"

static void Usage(const std::string porc)
{
  std::cout << "Usage:\n\t" << porc << " port [ip]" << std::endl;
}

/// @brief  我们想写一个简单的udpSever
/// 云服务器有一些特殊情况：
/// 1. 禁止你bind云服务器上的任何确定IP， 只能使用INADDR_ANY，如果你是虚拟机，随意
class UdpServer
{
public:
  UdpServer(int port, std::string ip = "") : _port((uint16_t)port), _ip(ip), _socketFd(-1)
  {
  }
  ~UdpServer()
  {
  }

public:
  void init()
  {
    // 1. 创建socket套接字
    _socketFd = socket(AF_INET, SOCK_DGRAM, 0); // 就是打开了一个文件
    if (_socketFd < 0)
    {
      logMessage(FATAL, "socket:%s:%d", strerror(errno), _socketFd);
      exit(1);
    }
    logMessage(DEBUG, "socket create success: %d", _socketFd);
    struct sockaddr_in local;     // local在哪里开辟的空间? 用户栈 -> 临时变量 -> 写入内核中
    bzero(&local, sizeof(local)); // memset
    local.sin_family = AF_INET;
    local.sin_port = htons(_port);
    local.sin_addr.s_addr = _ip.empty() ? htonl(INADDR_ANY) : inet_addr(_ip.c_str());
    if (bind(_socketFd, (const struct sockaddr *)&local, sizeof(local)) == -1)
    {
      logMessage(FATAL, "bind: %s:%d", strerror(errno), _socketFd);
      exit(2);
    }
    logMessage(DEBUG, "socket bind success: %d", _socketFd);
  }

  void start()
  {
    // 服务器设计的时候，服务器都是死循环
    char inbuffer[1024];  // 将来读取到的数据，都放在这里
    char outbuffer[1024]; // 将来发送的数据，都放在这里

    while (true)
    {
      memset(outbuffer, '\0', sizeof(outbuffer));
      struct sockaddr_in peer;      // 输出型参数
      socklen_t len = sizeof(peer); // 输入输出型参数

      // demo2
      //  UDP无连接的
      //  对方给你发了消息，你想不想给对方回消息？要的！后面的两个参数是输出型参数
      ssize_t s = recvfrom(_socketFd, inbuffer, sizeof(inbuffer) - 1, 0,
                           (struct sockaddr *)&peer, &len);
      if (s > 0)
      {
        inbuffer[s] = 0; // 当做字符串
      }
      else if (s == -1)
      {
        logMessage(WARINING, "recvfrom: %s:%d", strerror(errno), _socketFd);
        continue;
      }
      // 读取成功的,除了读取到对方的数据，你还要读取到对方的网络地址[ip:port]
      std::string peerIp = inet_ntoa(peer.sin_addr); // 拿到了对方的IP
      uint32_t peerPort = ntohs(peer.sin_port);      // 拿到了对方的port

      checkOnlineUser(peerIp, peerPort, peer); // 如果存在，什么都不做，如果不存在，就添加

      // 打印出来客户端给服务器发送过来的消息
      logMessage(NOTICE, "[%s:%d]# %s", peerIp.c_str(), peerPort, inbuffer);

      for (int i = 0; i < strlen(inbuffer); i++)
      {
        if (isalpha(inbuffer[i]) && islower(inbuffer[i]))
          outbuffer[i] = toupper(inbuffer[i]);
        else
          outbuffer[i] = toupper(inbuffer[i]);
      }
      messageRoute(peerIp, peerPort, inbuffer); // 消息路由

      // 线程池！

      // sendto(_socketFd, outbuffer, strlen(outbuffer), 0, (struct sockaddr *)&peer, len);
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
  // 服务器必须得有端口号信息
  uint16_t _port;
  // 服务器必须得有ip地址
  std::string _ip;
  // 服务器的socket fd信息
  int _socketFd;
  // onlineuser
  std::unordered_map<std::string, struct sockaddr_in> users;
};

// // struct client{
// //     struct sockaddr_in peer;
// //     uint64_t when; //peer如果在when之前没有再给我发消息，我就删除这用户
// // }

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

  UdpServer ser(port, ip);
  // std::cout << port << " " << ip << std::endl;
  ser.init();
  ser.start();
  return 0;
}

// int main()
// {
//     // 创建套接字
//     // int socket(int domain, int type, int protocol);
//     // 本地或者域间 数据包/字节序  协议类型--网络中直接为0
//     // 重要的 返回值就是一个文件描述符  -- 就是打开网卡这个文件 -- 我们这么认为,实际是不对的

//     // udpServer ser;
//     // ser.init();
//     // ser.start();
//     // 或者PF_INT   数据报 -- udp SOCK_DGRAM
//     int fd = socket(AF_INET, SOCK_DGRAM, 0);
//     if (fd < 0)
//     {
//         logMessage(FATAL, "%s : %d", strerror(errno), fd);
//         // cout << strerror(errno) << endl;
//         exit(1);
//     }
//     logMessage(DEBUG, "socket create success : %d", fd);

//     // cout << fd << endl;
//     return 0;
// }

// #include <iostream>
// #include <string>
// #include <unistd.h>

// #include <string.h>
// #include <cstring>
// #include <sys/types.h> /* See NOTES */
// #include <sys/socket.h>
// #include <errno.h>
// #include "Log.hpp"

// #include <netinet/in.h>
// #include <arpa/inet.h>

// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>

// using namespace std;

// ///@brief 服务端
// class udpServer
// {
// public:
//   udpServer(uint16_t port, const std::string &ip = "")
//       : _socketFd(-1), _port(port), _ip(ip)
//   {
//   }
//   ~udpServer() {}

// public:
//   void init()
//   {
//     // 1. 正式打开一个文件
//     // 域间   面向数据报
//     _socketFd = socket(AF_INET, SOCK_DGRAM, 0);
//     if (_socketFd < 0)
//     {
//       logMessage(FATAL, "%s : %d", strerror(errno), _socketFd);
//       exit(1);
//     }
//     logMessage(DEBUG, "创建套接字成功 : %d", _socketFd);

//     struct sockaddr_in local;
//     // 2. 填充信息
//     bzero(&local, sizeof local); // 初始化
//     local.sin_family = PF_INET;
//     local.sin_port = htons(_port);
//     local.sin_addr.s_addr = _ip.empty() ? INADDR_ANY : inet_addr(_ip.c_str());

//     if (bind(_socketFd, (const sockaddr *)&local, sizeof(local)) == -1)
//     {
//       logMessage(FATAL, "%s", strerror(errno));
//       exit(1);
//     }
//     logMessage(FATAL, "udp 套接字bind 成功");
//   }

//   void start()
//   {

//     char inbuffer[1024];  // 读去信息
//     char outbuffer[1024]; // 发送信息
//     while (true)
//     {
//       memset(inbuffer, '\0', sizeof(inbuffer));
//       // 正常进行网络读写
//       // 谁给我发消息,我们怎么会消息
//       // 后面两个参数是输出行参数
//       struct sockaddr_in peer;      // 输出型参数
//       socklen_t len = sizeof(peer); // 输入输出行参数
//       ssize_t s = recvfrom(_socketFd, inbuffer, sizeof(inbuffer) - 1, 0, (struct sockaddr *)&peer, &len);
//       if (s > 0)
//       {
//         inbuffer[s] = 0; // 当做字符串
//       }
//       else if (s == -1)
//       {
//         logMessage(WARINING, "recvfrom: %s:%d", strerror(errno), _socketFd);
//         continue;
//       }

//       // 读取成功的,除了读取到对方的数据，你还要读取到对方的网络地址[ip:port]
//       std::string peerIp = inet_ntoa(peer.sin_addr); // 拿到了对方的IP
//       uint16_t peerPort = ntohs(peer.sin_port);      // 拿到了对方的port
//       logMessage(NOTICE, "client# [%s:%d]# %s", peerIp.c_str(), peerPort, inbuffer);
//     }
//   }

// private:
//   int _socketFd;   // fd
//   uint16_t _port;  // 端口号
//   std::string _ip; // IP地址
// };
// static void Usage(const std::string proc)
// {
//   std::cout << "Usage:\n\t" << proc << "  port [ip]  " << std::endl;
// }

// int main(int argc, char *argv[])
// {
//   if (argc != 2 && argc != 3)
//   {
//     Usage(argv[0]);
//     exit(3);
//   }
//   int port = atoi(argv[1]);
//   //char *ip = nullptr;
//   std::string ip;

//   if (argc == 3)
//   {
//     ip = argv[2];
//   }

//   udpServer ser(port, ip);
//   ser.init();
//   ser.start();
//   return 0;
// }