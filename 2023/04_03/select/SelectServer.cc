/**
 * User: Qkj
 * Description:
 * Date: 2023-04-02
 * Time: 21:05
 */
#include <iostream>
#include <unistd.h>

#include <sys/select.h>
#include <errno.h>
#include <time.h>
#include "Sock.hpp"

int fdsArray[sizeof(fd_set) * 8] = {0}; // 保存所有合法的套接字
int gnum = sizeof(fdsArray) / sizeof(fdsArray[0]);
#define DFl -1 // 默认的文件描述符

static void
usage(std::string str)
{
  std::cerr << "\nUsage: " << str << " port\n"
            << std::endl;
}

/// @brief
/// @param listenSock  监听套接字
/// @param readfds  现在包含的就是已经读就绪的 文件描述符
static void HandlerEvent(int listenSock, fd_set &readfds)
{
  for (size_t i = 0; i < gnum; i++)
  {
    if (fdsArray[i] == DFl)
    {
      continue;
    }
    if (i == 0 && fdsArray[i] == listenSock)
    {
      if (FD_ISSET(listenSock, &readfds))
      {
        // 此时这里有一个新连接
        std::cout << "已经有一个新连接到来了, 需要进行获取了" << std::endl;
        std::string clientIP;
        uint16_t clientPort;
        int sock = Sock::Accept(listenSock, &clientIP, &clientPort);
        if (sock < 0)
          return;
        std::cout << "获取新连接成功" << clientIP
                  << " : " << clientPort
                  << "| sock : " << sock << std::endl;

        // 把新的文件描述符托管
        size_t i = 0;
        for (; i < gnum; i++)
        {
          if (fdsArray[i] == DFl)
            break;
        }
        if (i == gnum)
        {
          std::cout << "不好意思,我们文件描述符已经被用完了, 我的的服务器已经到达上限了" << std::endl;
          close(sock);
        }
        else
        {
          fdsArray[i] = sock;
        }
      }
    }
    else
    {
      // 处理普通为IO事件
      if (FD_ISSET(fdsArray[i], &readfds))
      {
        // 合法的不一定是就绪的
        char buffer[1024];
        ssize_t s = recv(fdsArray[i], buffer, sizeof(buffer) - 1, 0);
        if (s == 0)
        {
          // 对端关闭
          close(fdsArray[i]);
          fdsArray[i] = DFl;
        }
        else if (s > 0)
        {
          buffer[s] = '\0';
          std::cout << "client[ " << fdsArray[i] << " ]# " << buffer; // 这里不能抱枕我们可以读取完整的报文,这里我们后面epool同一解决
        }
        else
        {
          std::cerr << "出现了问题" << std::endl;
        }
      }
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    usage(argv[0]);
    exit(1);
  }
  int port = atoi(argv[1]);
  int listenSock = Sock::Socket(); //
  Sock::Bind(listenSock, port);
  Sock::Listen(listenSock);

  for (size_t i = 0; i < gnum; i++)
  {
    fdsArray[i] = DFl;
  }
  fdsArray[0] = listenSock; // 我们就认为0 好默认保存监听套接字

  while (true)
  {
    int maxFd = DFl;
    fd_set readfds;
    FD_ZERO(&readfds);

    for (int i = 0; i < gnum; i++)
    {
      if (fdsArray[i] == DFl)
      {
        continue;
      }
      FD_SET(fdsArray[i], &readfds); // 添加文件描述符

      // 更新 maxFd
      if (maxFd < fdsArray[i])
        maxFd = fdsArray[i];
    }

    struct timeval timeout = {100, 0};
    // int sock = Sock::Accept(listenSock, )
    int n = select(maxFd + 1, &readfds, nullptr, nullptr, &timeout);
    // int n = select(maxFd + 1, &readfds, nullptr, nullptr, nullptr); // 永久阻塞
    switch (n)
    {
    case 0:
      std::cout << "time out ... : " << (unsigned long)time(nullptr) << std::endl;
      break;
    case -1:
      std::cerr << "errno " << strerror(errno) << std::endl;
      break;
    default:
      HandlerEvent(listenSock, readfds);
      break;
    }
  }

  return 0;
}