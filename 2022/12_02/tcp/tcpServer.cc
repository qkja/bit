/**
 * Author       : Qkj
 * Description  : tcp套接字
 * Date         : 2022-11-27 10:39:59
 * LastEditTime : 2022-11-27 10:43:20
 */
#include "util.hpp"

class ServerTcp
{
public:
  ServerTcp(uint16_t port, const std::string &ip = "") : port_(port), ip_(ip), listenSock_(-1)
  {}
  ~ServerTcp()
  {}

public:
  void init()
  {
    // 1. 创建socket
    listenSock_ = socket(PF_INET, SOCK_STREAM, 0);
    if (listenSock_ < 0)
    {
      logMessage(FATAL, "socket: %s", strerror(errno));
      exit(SOCKET_ERR);
    }

    logMessage(DEBUG, "socket: %s, %d", strerror(errno), listenSock_);

    // 2. bind绑定
    // 2.1 填充服务器信息
    struct sockaddr_in local; // 用户栈
    memset(&local, 0, sizeof local);

    local.sin_family = PF_INET;
    local.sin_port = htons(port_);
    ip_.empty() ? (local.sin_addr.s_addr = INADDR_ANY) : (inet_aton(ip_.c_str(), &local.sin_addr));

    // 2.2 本地socket信息，写入sock_对应的内核区域
    if (bind(listenSock_, (const struct sockaddr *)&local, sizeof local) < 0)
    {
      logMessage(FATAL, "bind: %s", strerror(errno));
      exit(BIND_ERR);
    }

    logMessage(DEBUG, "bind: %s, %d", strerror(errno), listenSock_);

    // 3. 监听socket，为何要监听呢？tcp是面向连接的！
    if (listen(listenSock_, 5 /*后面再说*/) < 0)
    {
      logMessage(FATAL, "listen: %s", strerror(errno));
      exit(LISTEN_ERR);
    }

    logMessage(DEBUG, "listen: %s, %d", strerror(errno), listenSock_);
    // 运行别人来连接你了
  }

  void loop()
  {
    while (true)
    {

      struct sockaddr_in peer;
      socklen_t len = sizeof(peer);
      bzero(&peer, len);
      //  这是 获取新连接  喂
      // 放回置是一个   文件描述复    就是一个scoket
      // 这个就先像我们去外边旅游,主打得美食. 鱼庄
      // 有人是在酒店外面拉客,此时这个拉客的动作就是 accept
      // 如果拉克成功,这里就会出现另外一个服务员
      // 张三得 工作  -- 获取新得客源
      // 李四/王五   -- 给客户提供服务

      // 我们一直不知道len是什么意思,这里也不谈  等到后面我们谈原理得时候在所

      int serviceSock = accept(listenSock_, (struct sockaddr *)&peer, &len);
      if (serviceSock < 0)
      {
        // 如果不会拉客人成功,我们就会拉另外的客人
        // -1就会被返回
        logMessage(WARING, "accept %s:[%d]", strerror(errno), listenSock_);
        continue;
      }

      //  得到客户端得IP和port
      uint16_t peerPort = ntohs(peer.sin_port);
      std::string peerIp = inet_ntoa(peer.sin_addr);
      logMessage(DEBUG, "accept %s | %s[%d], scoket fd: %d", strerror(errno), peerIp.c_str(), peerPort, listenSock_);

      // 5 提供服务 echo 小写->变大写
      transService(serviceSock, peerIp, peerPort);
    }
  }

private:
  // 服务员套接字, 客户端IP, 客户端套接字
  void transService(int sock, const std::string &clientIP, uint16_t clientPort)
  {
    // p判断有效性
    assert(sock >= 0);
    assert(!clientIP.empty());
    assert(clientPort >= 1024);

    // 流式套接字 面向字节流
    // 用 read write  进行读写
    // 不能用  udp的那个 那个是 udp固有的
    char inBuffer[BUFFER_SIZE];
    while (true)
    {
      //
      ssize_t s = read(sock, inBuffer, sizeof(inBuffer) - 1);
      //std::cout << inBuffer<< std::endl;
      if (s > 0)
      {
        // 读取成功
        inBuffer[s] = '\0';
        if (strcasecmp(inBuffer, "quit") == 0)
          break;
        logMessage(DEBUG, " trans befor %s", inBuffer);
        // 大少写转化
        for (size_t i = 0; i < s; i++)
        {
          
          if (isalpha(inBuffer[i]) && islower(inBuffer[i]))
            inBuffer[i] = toupper(inBuffer[i]);
        }

        // 写回
        write(sock, inBuffer, strlen(inBuffer));
        // 管道只能一个读,一个写,为何tcp和udp可以这样
        // 证明了tcp和udp 支持全双工
        logMessage(DEBUG, " write succes");
      }
      else if (s == 0)
      {
        // 写端关闭   --> 对方关闭了,客户端退出
        logMessage(DEBUG, "客服端 %s %d 退出了", clientIP.c_str(), clientPort);
        break;
      }
      else
      {
        logMessage(DEBUG, "客服端 %s %d 出错了,错误信息:%s ", clientIP.c_str(), clientPort, strerror(errno));
        break;
      }
    }

    close(sock); // 服务都完了,人走茶凉 如果不关闭,打开文件总是有上限的 这个称之文件描述符泄漏.要知道进程是不退的
    logMessage(DEBUG, "close succes");
  }

private:
  // sock
  int listenSock_;
  // port
  uint16_t port_;
  // ip
  std::string ip_;
};

void Usage(const char *proc)
{
  std::cerr << "Usage:\n\t" << proc << " port [ip]" << std::endl;
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
    ip = argv[2];

  ServerTcp svr(port, ip);


  svr.init();
  svr.loop();
  return 0;
}
// 为何会有两类套接字

// 张三和李四都是服务员   张三又去等待客人,李四是被张三叫过来的,又叫了王五
// 张三的核心工作  -- 获取新客源  不提供给张三任何服务
// 王五等角色是  给客户提供服务
// 张三还在安心的等待客源,可是张三和李四都是人 为何是不同等工作

// 参数    --> 获取新的客源   监听套接字
// 放回值  提供服务的
// 验证说法
