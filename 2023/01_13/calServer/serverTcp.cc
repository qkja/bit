#include "Protocol.hpp"
#include "util.hpp"
#include "Task.hpp"
#include "ThreadPool.hpp"
#include "daemonize.hpp"

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
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

// 1. 全部手写
// 2. 部分采用别人的方案--序列化和反序列化的问题
void netCal(int sock, const std::string &clientIp, uint16_t clientPort)
{
  assert(sock >= 0);
  assert(!clientIp.empty());
  assert(clientPort >= 1024);

  // 9\r\n100 + 200\r\n    9\r\n112 / 200\r\n
  std::string inbuffer;
  while (true)
  {
    Request req;
    char buff[128];
    ssize_t s = read(sock, buff, sizeof(buff) - 1);
    if (s == 0)
    {
      logMessage(NOTICE, "client[%s:%d] close sock, service done", clientIp.c_str(), clientPort);
      break;
    }
    else if (s < 0)
    {
      logMessage(WARINING, "read client[%s:%d] error, errorcode: %d, errormessage: %s",
                 clientIp.c_str(), clientPort, errno, strerror(errno));
      break;
    }

    // read success
    buff[s] = 0;
    inbuffer += buff;
    // 1. 检查inbuffer是不是已经具有了一个strPackage
    uint32_t packageLen = 0;
    std::string package = decode(inbuffer, &packageLen); // TODO
    if (packageLen == 0)
      continue; // 无法提取一个完整的报文，继续努力读取吧
    // 2. 已经获得一个完整的package
    if (req.deserialize(package))
    {
      req.debug();
      // 3. 处理逻辑, 输入的是一个req，得到一个resp
      Response resp = calculator(req); // resp是一个结构化的数据
      // 4. 对resp进行序列化
      std::string respPackage;
      resp.serialize(&respPackage);
      // 5. 对报文进行encode -- //TODO
      respPackage = encode(respPackage, respPackage.size());
      // 6. 简单进行发送 -- 后续处理
      write(sock, respPackage.c_str(), respPackage.size());
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
  // static void *threadRoutine(void *args)
  // {
  //     pthread_detach(pthread_self()); //设置线程分离
  //     ThreadData *td = static_cast<ThreadData *>(args);
  //     td->this_->transService(td->sock_, td->clinetIp_, td->clientPort_);
  //     delete td;
  //     return nullptr;
  // }
  void loop()
  {
    // signal(SIGCHLD, SIG_IGN); // only Linux
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
      // 5 提供服务, echo -> 小写 -> 大写
      // 5.0 v0 版本 -- 单进程 -- 一旦进入transService，主执行流，就无法进行向后执行，只能提供完毕服务之后才能进行accept
      // transService(serviceSock, peerIp, peerPort);

      // 5.1 v1 版本 -- 多进程版本 -- 父进程打开的文件会被子进程继承吗？会的
      // pid_t id = fork();
      // assert(id != -1);
      // if(id == 0)
      // {
      //     close(listenSock_); //建议
      //     //子进程
      //     transService(serviceSock, peerIp, peerPort);
      //     exit(0); // 进入僵尸
      // }
      // // 父进程
      // close(serviceSock); //这一步是一定要做的！

      // 5.1 v1.1 版本 -- 多进程版本  -- 也是可以的
      // 爷爷进程
      // pid_t id = fork();
      // if(id == 0)
      // {
      //     // 爸爸进程
      //     close(listenSock_);//建议
      //     // 又进行了一次fork，让 爸爸进程
      //     if(fork() > 0) exit(0);
      //     // 孙子进程 -- 就没有爸爸 -- 孤儿进程 -- 被系统领养 -- 回收问题就交给了系统来回收
      //     transService(serviceSock, peerIp, peerPort);
      //     exit(0);
      // }
      // // 父进程
      // close(serviceSock); //这一步是一定要做的！
      // // 爸爸进程直接终止，立马得到退出码，释放僵尸进程状态
      // pid_t ret = waitpid(id, nullptr, 0); //就用阻塞式
      // assert(ret > 0);
      // (void)ret;

      // 5.2 v2 版本 -- 多线程
      // 这里不需要进行关闭文件描述符吗？？不需要啦
      // 多线程是会共享文件描述符表的！
      // ThreadData *td = new ThreadData(peerPort, peerIp, serviceSock, this);
      // pthread_t tid;
      // pthread_create(&tid, nullptr, threadRoutine, (void*)td);

      // 5.3 v3 版本 --- 线程池版本
      // 5.3.1 构建任务
      // 5.3 v3.1
      // Task t(serviceSock, peerIp, peerPort, std::bind(&ServerTcp::transService, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
      // tp_->push(t);

      // 5.3 v3.2
      // Task t(serviceSock, peerIp, peerPort, transService);
      // tp_->push(t);
      // 5.3 v3.3
      // Task t(serviceSock, peerIp, peerPort, execCommand);
      // tp_->push(t);

      // 5.4 v3.3
      Task t(serviceSock, peerIp, peerPort, netCal);
      tp_->push(t);

      // waitpid(); 默认是阻塞等待！WNOHANG
      // 方案1

      // logMessage(DEBUG, "server 提供 service start ...");
      // sleep(1);
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