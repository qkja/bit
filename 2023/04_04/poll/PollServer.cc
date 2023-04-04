// select 的输入输出是同一个参数,也就是我们每一次进行select
// 都要对参数进行重新设定

// poll 解决了select的两个问题
// 每一次都要对参数进行重新设计  -- 添加了一个结构体
// 服务器承载量是有上限的       -- 使用数组

// 理解事件 enent POLLIN  可读  POLLOUT 可写
#include "Sock.hpp"
#define NUM 1024

struct pollfd fdsArray[NUM];

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
static void HandlerEvent(int listenSock)
{
  for (size_t i = 0; i < NUM; i++)
  {
    if (fdsArray[i].fd == DFl)
    {
      continue;
    }

    if (i == 0 && fdsArray[i].fd == listenSock)
    {
      if (fdsArray[i].revents & POLLIN)
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
        for (; i < NUM; i++)
        {
          if (fdsArray[i].fd == DFl)
            break;
        }
        if (i == NUM)
        {
          std::cout << "不好意思,我们文件描述符已经被用完了, 我的的服务器已经到达上限了" << std::endl;
          close(sock);
        }
        else
        {
          fdsArray[i].fd = sock;
          fdsArray[i].events = POLLIN;
          fdsArray[i].revents = 0;
        }
      }
    }
    else
    {
      // 处理普通为IO事件
      if (fdsArray[i].revents & POLLIN)
      {
        // 合法的不一定是就绪的
        char buffer[1024];
        ssize_t s = recv(fdsArray[i].fd, buffer, sizeof(buffer) - 1, 0);
        if (s == 0)
        {
          // 对端关闭
          close(fdsArray[i].fd);
          fdsArray[i].fd = DFl;
          fdsArray[i].events = 0;
          fdsArray[i].revents = 0;
        }
        else if (s > 0)
        {
          buffer[s] = '\0';
          std::cout << "client[ " << fdsArray[i].fd << " ]# " << buffer; // 这里不能抱枕我们可以读取完整的报文,这里我们后面epool同一解决
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

  for (size_t i = 0; i < NUM; i++)
  {
    fdsArray[i].fd = DFl;
    fdsArray[i].events = 0;
    fdsArray[i].revents = 0;
  }
  fdsArray[0].fd = listenSock;
  fdsArray[0].events = POLLIN; // 用户告诉内核
  int timeout = 1000;          // 1s
  while (true)
  {

    int n = poll(fdsArray, NUM, timeout);  // -1 就是阻塞
    switch (n)
    {
    case 0:
      std::cout << "time out ... : " << (unsigned long)time(nullptr) << std::endl;
      break;
    case -1:
      std::cerr << "errno " << strerror(errno) << std::endl;
      break;
    default:
      HandlerEvent(listenSock);
      break;
    }
  }

  return 0;
}

// 问题 poll 有上限吗 ? 没有  ,但是上面我们数组不是固定的吗?这里我们这么理解 
// 所谓的上限是我们在经过一定的努力仍旧打破不了我们的上限