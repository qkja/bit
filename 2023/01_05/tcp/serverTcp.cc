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

  void start()
  {
    //accept(); //返回值 值最关键的  是一个新的socket ??
    while (true)
    {
      logMessage(DEBUG, "server ...");
      sleep(1);
    }
    
  }

private:
  int _sock;
  uint16_t _port;
  std::string _ip; // ip地址
};

int main()
{
  ServerTcp server(8080);
  server.init();
  server.start();
  return 0;
}