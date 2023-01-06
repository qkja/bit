#include "util.hpp"

class ServerTcp
{
public:
  ServerTcp(uint16_t port, std::string ip = "")
      : _sock(-1), _port(port), _ip(ip)
  {
  }
  ~ServerTcp()
  {
  }

public:
  void init()
  {

    // 1. 创建套接字
    _sock = socket(AF_INET, SOCK_STREAM, 0); // 面向数据报的
    if (_sock < 0)
    {
      logMessage(FATAL, "%s:%d", strerror(errno), _sock);
      exit(SOCKET_ERR);
    }

    logMessage(DEBUG, "socket %s:%d", strerror(errno), _sock);

    // 2. bind
    // 2.1 填充信息
    struct sockaddr_in local;
    memset(&local, 0, sizeof(local));

    local.sin_family = PF_INET;
    local.sin_port = htons(_port);
    _ip.empty() ? (local.sin_addr.s_addr = htonl(INADDR_ANY))
                : inet_aton(_ip.c_str(), &local.sin_addr);
    // 2.2 绑定
    if (bind(_sock, (const struct sockaddr *)&local, sizeof(local)) == -1)
    {
      logMessage(FATAL, "%s:%d", strerror(errno), _sock);
      exit(BIND_ERR);
    }
    logMessage(DEBUG, "bind %s:%d", strerror(errno), _sock);

    // 3. 监听sock udp是面向连接的 做任何事之前先干什么
    if (listen(_sock, 5) < 0) // 5 这个第二参数后面在谈
    {
      logMessage(FATAL, "%s:%d", strerror(errno), _sock);
      exit(LISTEN_ERR);
    }
    logMessage(DEBUG, "listen %s:%d", strerror(errno), _sock);
  }

  void loop()
  {
    signal(SIGCHLD, SIG_IGN); // 仅在Linux下有效
    // accept(); //返回值 值最关键的  是一个新的socket ??
    while (true)
    {
      struct sockaddr_in peer;
      socklen_t len = sizeof(peer);

      int serviceSock = accept(_sock, (struct sockaddr *)&peer, &len);
      if (serviceSock < 0)
      {
        logMessage(FATAL, "%s:%d", strerror(errno), _sock);
        continue;
      }

      // 4. 获取客户端的基本信息
      std::string peerIP = inet_ntoa(peer.sin_addr);
      uint16_t peerPort = ntohs(peer.sin_port);
      logMessage(DEBUG, "accept: %s | %s[%d] sockfd %d",
                 strerror(errno), peerIP.c_str(), peerPort, serviceSock);
      // 5. 提供服务
      // 5.0 版本 服务是单进程的
      // transService(serviceSock, peerIP, peerPort);

      // 5.1 多进程版本
      pid_t id = fork();

      assert(id != -1); // 服务器都挂了

      if (0 == id)
      {
        // 建议关掉 监听套接字
        close(_sock);
        // 子进程
        transService(serviceSock, peerIP, peerPort);
        exit(0);
      }

      // 父进程  -- 不需要对外提供服务 父进程的文件描述符会被子进程继承吗?会的,写时拷贝
      // 那么父进程也要关闭自己的文件描述(写时拷贝)
      close(serviceSock);
      // 父进程如何关心 子进程 回收资源 非阻塞可以,但是这里不建议 需要轮询检测
      // 子进程在退出的时候会发送一个信号 这个就可以了

      // logMessage(DEBUG, "server ...");
      // sleep(1);
    }
  }

private:
  // void transService(int sock, const std::string &peerIP, const uint16_t &peerPort)
  void transService(int sock, const std::string peerIP, const uint16_t peerPort)
  {
    assert(sock > 0);
    assert(!peerIP.empty());
    // 读取客户的输入
    char inbuffer[1024];
    while (true)
    {
      memset(inbuffer, '\0', sizeof(inbuffer));
      // udp 的我们不能用  这是流式的吗? 是的
      ssize_t s = read(sock, inbuffer, sizeof(inbuffer) - 1);
      if (s > 0)
      {
        inbuffer[s] = '\0';
        if (strcasecmp(inbuffer, "quit") == 0)
        {
          logMessage(DEBUG, "客端退出了 %s[%d]", peerIP.c_str(), peerPort);
          break;
        }
        logMessage(DEBUG, "trans before: [%s][%d]>>> %s", peerIP.c_str(), peerPort, inbuffer);

        // 目前提供的服务事大小写转化
        for (int i = 0; i < s; i++)
        {
          if (isalpha(inbuffer[i]) && islower(inbuffer[i]))
            inbuffer[i] = toupper(inbuffer[i]);
        }
        logMessage(DEBUG, "trans after: [%s][%d]>>> %s", peerIP.c_str(), peerPort, inbuffer);

        // 此时响应回去  write
        write(sock, inbuffer, strlen(inbuffer));

        // 为何可以读写 --  这是tcp或者udp 支持的,
      }
      else if (s == 0)
      {
        // 有一段关闭了 此时这一端读到的就是0
        logMessage(DEBUG, "客端退出了 %s[%d]", peerIP.c_str(), peerPort);
        break;
      }
      else
      {
        logMessage(DEBUG, "读取出错 %s %s[%d]", strerror(errno), peerIP.c_str(), peerPort);
        break;
      }
    }

    // 走到这里一定事退出了  服务到此结束
    // 回收资源
    close(sock);
    logMessage(DEBUG, "server close %d done", sock);
  }

private:
  int _sock; // 监听套接字
  uint16_t _port;
  std::string _ip; // ip地址
};

static void Usage(char *proc)
{
  std::cerr << "Usage:\n\t" << proc << " port ip" << std::endl;
}

// .serverTcp port, port
int main(int argc, char *argv[])
{

  if (argc != 2 && argc != 3)
  {
    Usage(argv[0]);
    exit(USAGE_ERR);
  }

  std::string ip;
  uint16_t port = atoi(argv[1]);
  if (argc == 3)
  {
    ip = argv[2];
  }

  ServerTcp server(port, ip);
  server.init();
  server.loop();
  return 0;
}