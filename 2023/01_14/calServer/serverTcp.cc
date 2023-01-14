#include "Protocol.hpp"
#include "util.hpp"
#include "Task.hpp"
#include "ThreadPool.hpp"
#include "daemonize.hpp"
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <cstring>
#include <cerrno>

class ServerTcp; // 申明一下ServerTcp

// 大小写转化服务
// TCP && UDP: 支持全双工
void transService(int sock, const std::string &clientIp, uint16_t clientPort)
{
  assert(sock >= 0);
  assert(!clientIp.empty());
  assert(clientPort >= 1024);

  char inbuffer[BUFFER_SIZE];
  while (true)
  {
    ssize_t s = read(sock, inbuffer, sizeof(inbuffer) - 1); // 我们认为我们读到的都是字符串
    if (s > 0)
    {
      // read success
      inbuffer[s] = '\0';
      if (strcasecmp(inbuffer, "quit") == 0)
      {
        logMessage(DEBUG, "client quit -- %s[%d]", clientIp.c_str(), clientPort);
        break;
      }
      logMessage(DEBUG, "trans before: %s[%d]>>> %s", clientIp.c_str(), clientPort, inbuffer);
      // 可以进行大小写转化了
      for (int i = 0; i < s; i++)
      {
        if (isalpha(inbuffer[i]) && islower(inbuffer[i]))
          inbuffer[i] = toupper(inbuffer[i]);
      }
      logMessage(DEBUG, "trans after: %s[%d]>>> %s", clientIp.c_str(), clientPort, inbuffer);

      write(sock, inbuffer, strlen(inbuffer));
    }
    else if (s == 0)
    {
      // pipe: 读端一直在读，写端不写了，并且关闭了写端，读端会如何？s == 0，代表对端关闭
      // s == 0: 代表对方关闭,client 退出
      logMessage(DEBUG, "client quit -- %s[%d]", clientIp.c_str(), clientPort);
      break;
    }
    else
    {
      logMessage(DEBUG, "%s[%d] - read: %s", clientIp.c_str(), clientPort, strerror(errno));
      break;
    }
  }

  // 只要走到这里，一定是client退出了，服务到此结束
  close(sock); // 如果一个进程对应的文件fd，打开了没有被归还，文件描述符泄漏！
  logMessage(DEBUG, "server close %d done", sock);
}

void execCommand(int sock, const std::string &clientIp, uint16_t clientPort)
{
  assert(sock >= 0);
  assert(!clientIp.empty());
  assert(clientPort >= 1024);

  char command[BUFFER_SIZE];
  while (true)
  {
    ssize_t s = read(sock, command, sizeof(command) - 1); // 我们认为我们读到的都是字符串
    if (s > 0)
    {
      command[s] = '\0';
      logMessage(DEBUG, "[%s:%d] exec [%s]", clientIp.c_str(), clientPort, command);
      // 考虑安全
      std::string safe = command;
      if ((std::string::npos != safe.find("rm")) || (std::string::npos != safe.find("unlink")))
      {
        break;
      }
      // 我们是以r方式打开的文件，没有写入
      // 所以我们无法通过dup的方式得到对应的结果
      FILE *fp = popen(command, "r");
      if (fp == nullptr)
      {
        logMessage(WARINING, "exec %s failed, beacuse: %s", command, strerror(errno));
        break;
      }
      char line[1024];
      while (fgets(line, sizeof(line) - 1, fp) != nullptr)
      {
        write(sock, line, strlen(line));
      }
      // dup2(fd, 1);
      // dup2(sock, fp->_fileno);
      // fflush(fp);
      pclose(fp);
      logMessage(DEBUG, "[%s:%d] exec [%s] ... done", clientIp.c_str(), clientPort, command);
    }
    else if (s == 0)
    {
      // pipe: 读端一直在读，写端不写了，并且关闭了写端，读端会如何？s == 0，代表对端关闭
      // s == 0: 代表对方关闭,client 退出
      logMessage(DEBUG, "client quit -- %s[%d]", clientIp.c_str(), clientPort);
      break;
    }
    else
    {
      logMessage(DEBUG, "%s[%d] - read: %s", clientIp.c_str(), clientPort, strerror(errno));
      break;
    }
  }

  // 只要走到这里，一定是client退出了，服务到此结束
  close(sock); // 如果一个进程对应的文件fd，打开了没有被归还，文件描述符泄漏！
  logMessage(DEBUG, "server close %d done", sock);
}




/// @brief 这个是一个计算  也就是服务端计算结果的
/// @param req 
/// @return 
static Response calculator(const Request &req)
{
  Response resp;
  switch (req.op_)
  {
  case '+':
    resp.result_ = req.x_ + req.y_;
    break;
  case '-':
    resp.result_ = req.x_ - req.y_;
    break;
  case '*':
    resp.result_ = req.x_ * req.y_;
    break;
  case '/':
  { // x_ / y_
    if (req.y_ == 0)
      resp.exitCode_ = -1; // -1. 除0
    else
      resp.result_ = req.x_ / req.y_;
  }
  break;
  case '%':
  { // x_ / y_
    if (req.y_ == 0)
      resp.exitCode_ = -2; // -2. 模0
    else
      resp.result_ = req.x_ % req.y_;
  }
  break;
  default:
    resp.exitCode_ = -3; // -3: 非法操作符
    break;
  }

  return resp;
}


void netCal(int sock, const std::string &clientIp, uint16_t clientPort)
{
  assert(sock >= 0);
  assert(!clientIp.empty());
  assert(clientPort >= 1024);

  std::string inbuffer;
  while (1)
  {
    Request req;  // 请求
    char buff[128];

    // tcp不一定全部发完,我们这里读取有很多的细节
    ssize_t s = read(sock, buff, sizeof(buff));

    if (s == 0)
    {
      // 关了,我们什么也做不了,注意底层和 管道差不多,只有关了才会读出0
      logMessage(NOTICE, "client[%s:%d] close sock,server done", clientIp.c_str(), clientPort);
      break;
    }
    else if (s < 0)
    {
      logMessage(WARINING, "read client[%s:%d] errno, errnocode %d %s",
                 clientIp.c_str(),
                 clientPort,
                 errno,
                 strerror(errno));
      break;
    }

    // 到这里就读取到数据了
    buff[s] = '\0';  // 把他变成字符串风格
    inbuffer += buff; 
    // 此时我们需要检测 读取的字符串是不是够一个报文的
    uint32_t packagaLen = 0; // 有效载荷的长度
    // 此时开始解包
    std::string package = decode(inbuffer, &packagaLen);

    if (packagaLen == 0)
      continue;

    // 到这里我们已经解包成功了,需要对请求进行反序列化
    if (req.deserialize(package))
    {
      // 放序列化成功, 打印一下
      req.debug();
      // 计算结果,顺便把结果保存到结构体中
      Response resp = calculator(req);

      // 我们需要进行序列化 这里已经拿到结果了,我们需要把结果给序列化了
      std::string respPackage;
      resp.serialize(&respPackage);

      // 对结果添加添加包头
      respPackage = encode(respPackage, respPackage.size());
      // 这里可以发了 我们一次会发多少字节,后面同意解决,这里很简单,主要是代码会变的非常乱
      write(sock, respPackage.c_str(), respPackage.size());
    }
    else
    {
      // 这里的请求不符合要求,暂时什么都不做
    }
  }
}

























class ThreadData
{
public:
  uint16_t clientPort_;
  std::string clinetIp_;
  int sock_;
  ServerTcp *this_;

public:
  ThreadData(uint16_t port, std::string ip, int sock, ServerTcp *ts)
      : clientPort_(port), clinetIp_(ip), sock_(sock), this_(ts)
  {
  }
};

class ServerTcp
{
public:
  ServerTcp(uint16_t port, const std::string &ip = "")
      : port_(port),
        ip_(ip),
        listenSock_(-1),
        tp_(nullptr)
  {
    quit_ = false;
  }
  ~ServerTcp()
  {
    if (listenSock_ >= 0)
      close(listenSock_);
  }

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

    // 4. 加载线程池
    tp_ = ThreadPool<Task>::getInstance();
  }

  void loop()
  {
    // 启动线程池
    tp_->start();
    logMessage(DEBUG, "thread pool start success, thread num: %d", tp_->threadNum());

    while (!quit_)
    {
      struct sockaddr_in peer;
      socklen_t len = sizeof(peer);
      // 4. 获取连接, accept 的返回值是一个新的socket fd ？？
      // 4.1 listenSock_: 监听 && 获取新的链接-> sock
      // 4.2 serviceSock: 给用户提供新的socket服务
      int serviceSock = accept(listenSock_, (struct sockaddr *)&peer, &len);
      if (quit_)
        break;
      if (serviceSock < 0)
      {
        // 获取链接失败
        logMessage(WARINING, "accept: %s[%d]", strerror(errno), serviceSock);
        continue;
      }
      // 4.1 获取客户端基本信息
      uint16_t peerPort = ntohs(peer.sin_port);
      std::string peerIp = inet_ntoa(peer.sin_addr);

      logMessage(DEBUG, "accept: %s | %s[%d], socket fd: %d",
                 strerror(errno), peerIp.c_str(), peerPort, serviceSock);
      // 这里就是任务
      Task t(serviceSock, peerIp, peerPort, netCal);
      tp_->push(t);
    }
  }

  bool quitServer()
  {
    quit_ = true;
  }

private:
  // sock
  int listenSock_;
  // port
  uint16_t port_;
  // ip
  std::string ip_;
  // 引入线程池
  ThreadPool<Task> *tp_;
  // 安全退出
  bool quit_;
};

static void Usage(std::string proc)
{
  std::cerr << "Usage:\n\t" << proc << " port ip" << std::endl;
  std::cerr << "example:\n\t" << proc << " 8080 127.0.0.1\n"
            << std::endl;
}

ServerTcp *svrp = nullptr;

void sigHandler(int signo)
{
  if (signo == 3 && svrp != nullptr)
    svrp->quitServer();
  logMessage(DEBUG, "server quit save!");
}

// ./ServerTcp local_port local_ip
int main(int argc, char *argv[])
{
  if (argc != 2 && argc != 3)
  {
    Usage(argv[0]);
    exit(USAGE_ERR);
  }
  uint16_t port = atoi(argv[1]);
  std::string ip;
  if (argc == 3)
    ip = argv[2];

  // daemonize(); // 我们的进程就会成为守护进程
  signal(3, sigHandler);
  // Log log;
  // log.enable();
  ServerTcp svr(port, ip);
  svr.init();
  svrp = &svr;
  svr.loop();
  return 0;
}