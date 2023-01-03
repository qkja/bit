// #include <iostream>
// #include <string>
// #include <cstring>
// #include <unistd.h>
// #include <stdlib.h>
// #include <ctype.h>
// #include <unordered_map>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>

// #include "Log.hpp"

// static void Usage(const std::string porc)
// {
//     std::cout << "Usage:\n\t" << porc << " port [ip]" << std::endl;
// }

// /// @brief  我们想写一个简单的udpSever
// /// 云服务器有一些特殊情况：
// /// 1. 禁止你bind云服务器上的任何确定IP， 只能使用INADDR_ANY，如果你是虚拟机，随意
// class UdpServer
// {
// public:
//     UdpServer(int port, std::string ip = "") : port_((uint16_t)port), ip_(ip), sockfd_(-1)
//     {
//     }
//     ~UdpServer()
//     {
//     }

// public:
//     // public:
//     //   void init()
//     //   {
//     //     _socketFd = socket(AF_INET, SOCK_DGRAM, 0);
//     //     if (_socketFd < 0)
//     //     {
//     //       logMessage(FATAL, "%s : %d", strerror(errno), _socketFd);
//     //       exit(1);
//     //     }
//     //     logMessage(DEBUG, "socket create success : %d", _socketFd);

//     //     struct sockaddr_in local;
//     //     bzero(&local, sizeof(local)); // 初始化一下

//     //     local.sin_family = AF_INET;
//     //     local.sin_port = htons(_port);
//     //     local.sin_addr.s_addr = _ip.empty() ? htonl(INADDR_ANY) : inet_addr(_ip.c_str());

//     //     if (bind(_socketFd, (sockaddr *)&local, sizeof(local) == -1))
//     //     {
//     //       logMessage(FATAL, "%s:%d", strerror(errno), _socketFd);
//     //       exit(2);
//     //     }
//     //     logMessage(DEBUG, "socket bind success : %d", _socketFd);
//     //   }
//     void init()
//     {
//         // 1. 创建socket套接字
//         sockfd_ = socket(AF_INET, SOCK_DGRAM, 0); // 就是打开了一个文件
//         if (sockfd_ < 0)
//         {
//             logMessage(FATAL, "socket:%s:%d", strerror(errno), sockfd_);
//             exit(1);
//         }
//         logMessage(DEBUG, "socket create success: %d", sockfd_);
//         struct sockaddr_in local;     // local在哪里开辟的空间? 用户栈 -> 临时变量 -> 写入内核中
//         bzero(&local, sizeof(local)); // memset
//         local.sin_family = AF_INET;
//         local.sin_port = htons(port_);
//         local.sin_addr.s_addr = ip_.empty() ? htonl(INADDR_ANY) : inet_addr(ip_.c_str());
//         if (bind(sockfd_, (const struct sockaddr *)&local, sizeof(local)) == -1)
//         {
//             logMessage(FATAL, "bind: %s:%d", strerror(errno), sockfd_);
//             exit(2);
//         }
//         logMessage(DEBUG, "socket bind success: %d", sockfd_);
//     }

//     void start()
//     {
//         // 服务器设计的时候，服务器都是死循环
//         char inbuffer[1024];  // 将来读取到的数据，都放在这里
//         char outbuffer[1024]; // 将来发送的数据，都放在这里
//         while (true)
//         {
//             struct sockaddr_in peer;      // 输出型参数
//             socklen_t len = sizeof(peer); // 输入输出型参数

//             // demo2
//             //  UDP无连接的
//             //  对方给你发了消息，你想不想给对方回消息？要的！后面的两个参数是输出型参数
//             ssize_t s = recvfrom(sockfd_, inbuffer, sizeof(inbuffer) - 1, 0,
//                                  (struct sockaddr *)&peer, &len);
//             if (s > 0)
//             {
//                 inbuffer[s] = 0; // 当做字符串
//             }
//             else if (s == -1)
//             {
//                 logMessage(WARINING, "recvfrom: %s:%d", strerror(errno), sockfd_);
//                 continue;
//             }
//             // 读取成功的,除了读取到对方的数据，你还要读取到对方的网络地址[ip:port]
//             std::string peerIp = inet_ntoa(peer.sin_addr); // 拿到了对方的IP
//             uint32_t peerPort = ntohs(peer.sin_port);      // 拿到了对方的port

//             checkOnlineUser(peerIp, peerPort, peer); // 如果存在，什么都不做，如果不存在，就添加

//             // 打印出来客户端给服务器发送过来的消息
//             logMessage(NOTICE, "[%s:%d]# %s", peerIp.c_str(), peerPort, inbuffer);

//             // for(int i = 0; i < strlen(inbuffer); i++)
//             // {
//             //     if(isalpha(inbuffer[i]) && islower(inbuffer[i])) outbuffer[i] = toupper(inbuffer[i]);
//             //     else outbuffer[i] = toupper(inbuffer[i]);
//             // }
//             messageRoute(peerIp, peerPort, inbuffer); // 消息路由

//             // 线程池！

//             // sendto(sockfd_, outbuffer, strlen(outbuffer), 0, (struct sockaddr*)&peer, len);

//             // demo1
//             // logMessage(NOTICE, "server 提供 service 中....");
//             // sleep(1);
//         }
//     }

//     void checkOnlineUser(std::string &ip, uint32_t port, struct sockaddr_in &peer)
//     {
//         std::string key = ip;
//         key += ":";
//         key += std::to_string(port);
//         auto iter = users.find(key);
//         if (iter == users.end())
//         {
//             users.insert({key, peer});
//         }
//         else
//         {
//             // iter->first, iter->second->
//             // do nothing
//         }
//     }

//     void messageRoute(std::string ip, uint32_t port, std::string info)
//     {

//         std::string message = "[";
//         message += ip;
//         message += ":";
//         message += std::to_string(port);
//         message += "]# ";
//         message += info;

//         for (auto &user : users)
//         {
//             sendto(sockfd_, message.c_str(), message.size(), 0, (struct sockaddr *)&(user.second), sizeof(user.second));
//         }
//     }

// private:
//     // 服务器必须得有端口号信息
//     uint16_t port_;
//     // 服务器必须得有ip地址
//     std::string ip_;
//     // 服务器的socket fd信息
//     int sockfd_;
//     // onlineuser
//     std::unordered_map<std::string, struct sockaddr_in> users;
// };

// // struct client{
// //     struct sockaddr_in peer;
// //     uint64_t when; //peer如果在when之前没有再给我发消息，我就删除这用户
// // }

// // ./udpServer port [ip]
// int main(int argc, char *argv[])
// {
//     if (argc != 2 && argc != 3) // 反面：argc == 2 || argc == 3
//     {
//         Usage(argv[0]);
//         exit(3);
//     }
//     uint16_t port = atoi(argv[1]);
//     std::string ip;
//     if (argc == 3)
//     {
//         ip = argv[2];
//     }

//     UdpServer svr(port, ip);
//     svr.init();
//     svr.start();

//     return 0;
// }

// struct ip
// {
//     uint32_t part1:8;
//     uint32_t part2:8;
//     uint32_t part3:8;
//     uint32_t part4:8;
// }
// struct ip ip_;
// ip_.part1 = s.substr();

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Log.hpp"

using namespace std;
static void Usage(const std::string proc)
{
    std::cout << "Usage:\n\t" << proc << "  port [ip]  " << std::endl;
}
class udpServer
{
public:
    udpServer(int port, std::string ip = "") : _ip(ip), _port(port), _socketFd(-1)
    {
    }
    ~udpServer()
    {
    }

public:
    void init()
    {
        // 1. 正式打开一个文件
        _socketFd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_socketFd < 0)
        {
            logMessage(FATAL, "%s : %d", strerror(errno), _socketFd);
            exit(1);
        }
        logMessage(DEBUG, "socket create success : %d", _socketFd);

        // 2. 绑定网络信息
        // 2.1 填充信息  这个需要 包含头文件 man inet_addr
        struct sockaddr_in local;
        bzero(&local, sizeof(local)); // 初始化一下

        // 2.2 填充字段
        // 域
        local.sin_family = AF_INET;
        // 端口号 请问端口号要不要发给对方-- 一定要的 转大端
        local.sin_port = htons(_port);

        // 是不是要有IP地址 xx.yy.zz.aaa 字符串风格点分十进制 每一个居委u
        // 字符串占据的字节实在是太大了0到255 也就是 两个字节占据一个
        // 原理就是位端 的应用
        // struct ip
        // {
        //   uint32_t part1:8;
        //   uint32_t part2:8;
        //   uint32_t part3:8;
        //   uint32_t part4:8;
        // };
        // 有需要学习一个函数  字符串转整形
        // 注意我们用的是云服务器,有些情况
        // INADDR_ANY 就是一个0值,程序员不关系bind到哪一个ip,一台服务器可能有多个ip
        // 所有ip都绑定,报文到来了才进行分析是一个ip  云服务禁止使用绑定任何确定的ip
        //
        // in_addr_t inet_addr(const char *cp);ip 地址会不会发给对方 会的,这个已经转成大端了
        local.sin_addr.s_addr = _ip.empty() ? htonl(INADDR_ANY) : inet_addr(_ip.c_str());

        // 2.3 此时local在哪里开辟的空间 在内存的用户栈上
        // 临时变量要写入内核中  bind网络信息
        // int bind(int sockfd, const struct sockaddr *addr,
        //             socklen_t addrlen);
        if (bind(_socketFd, (const struct sockaddr *)&local, sizeof(local)) == -1)
        {
            logMessage(FATAL, "%s:%d", strerror(errno), _socketFd);
            exit(2);
        }
        // 对于udp服务器我们这里就完成了
        logMessage(DEBUG, "socket bind success : %d", _socketFd);
    }

    void start()
    {
        // 服务器都是死循环
        while (true)
        {
            logMessage(NOTICE, "server 提供服务中");
            sleep(1);
        }
        // char inbuffer[1024];  // 读去信息
        // char outbuffer[1024]; // 发送信息
        // while (true)
        // {
        //   memset(inbuffer, '\0', sizeof(inbuffer));
        //   // 正常进行网络读写
        //   // 谁给我发消息,我们怎么会消息
        //   // 后面两个参数是输出行参数
        //   struct sockaddr_in peer;      // 输出型参数
        //   socklen_t len = sizeof(peer); // 输入输出行参数
        //   ssize_t s = recvfrom(_socketFd, inbuffer, sizeof(inbuffer) - 1, 0, (struct sockaddr *)&peer, &len);
        //   if (s > 0)
        //   {
        //     inbuffer[s] = '\0';
        //   }
        //   else if (s == -1)
        //   {
        //     logMessage(WARINING, "读取失败 %s", strerror(errno));
        //     continue;
        //   }
        //   // 到这里一定读取成功了
        //  // logMessage(NOTICE, "读取失败 %s", strerror(errno));
        //  std::string peerIP = ;

        // }
    }

private:
    int _socketFd;   // fd
    uint16_t _port;  // 端口号
    std::string _ip; // ip地址
};
int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 3)
    {
        Usage(argv[0]);
        exit(3);
    }
    int port = atoi(argv[1]);
    char *ip;

    if (argc == 3)
    {
        ip = argv[2];
    }

    udpServer ser(port, ip);
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