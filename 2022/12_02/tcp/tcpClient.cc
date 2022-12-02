/**
 * Author       : Qkj
 * Description  :
 * Date         : 2022-11-27 10:39:49
 * LastEditTime : 2022-11-27 10:43:14
 */

#include "util.hpp"
volatile bool quit = false;

void Usage(const char *proc)
{
  std::cerr << "Usage:\n\t" << proc << " port [ip]" << std::endl;
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    Usage(argv[0]);
    exit(3);
  }
  // 得到 server的端口号 ip
  int port = atoi(argv[2]);
  std::string ip;
  if (argc == 3)
    ip = argv[1];
  // 出现一个套接字
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
    exit(1);
  }

  // 需要绑定吗       -- 不需要    但是不需要自己显式
  // 那么如何告知
  // 需要监听         --    不需要
  // 需要 asscpt 吗   -- 不要

  // 那么需要是什么? 发起连接
  struct sockaddr_in server;
  memset(&server, 0, sizeof(server));

  // 发起连接 先谁发起
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  inet_aton(ip.c_str(), &server.sin_addr);

  if (connect(sock, (const struct sockaddr *)&server, sizeof(server)) != 0)
  {
    std::cout << "连接失败" << std::endl;
    exit(1);
  }
  std::cout << "连接成功" << std::endl;
  std::string message;
  while (!quit)
  {
    message.clear();
    std::cout << "请输入你的消息# ";
    // std::cout << "请输入你的消息# ";
    // std::cin >> message;
    //  std::getline()
    std::getline(std::cin, message);
    // std::cout << "请输入你的消息# ";
    // fflush(stdout);
    std::cout << message << std::endl;
    if (strcasecmp(message.c_str(), "quit") == 0)
    {
      quit = true;
    }
    // std::cout << "请输入你的消息1# ";
    // fflush(stdout);

    ssize_t s = write(sock, (char *)message.c_str(), message.size());
    // std::cout << "请输入你的消息#2 ";
    // std::cout << "请输入你的消息2# ";
    // fflush(stdout);

    // std::cout << std::endl
    //           << s << std::endl;
    if (s > 0)
    {
      //如何读

      message.resize(1024);
      ssize_t ss = read(sock, (char *)message.c_str(), 1024);
      // ssize_t ss = 0;
      // std::cout << "请输入你的消息3# ";
      fflush(stdout);
      if (ss > 0)
      {
        message[ss] = '\0';
        std::cout << "server echo>> " << message << std::endl;
      }
    }
    else if (s <= 0)
    {
      break;
    }
  }

  close(sock);
  return 0;
}