/**
 * Author       : Qkj
 * Description  :
 * Date         : 2022-11-27 10:39:49
 * LastEditTime : 2022-11-27 10:43:14
 */

#include "util.hpp"

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
  int port = atoi(argv[1]);
  std::string ip;
  if (argc == 3)
    ip = argv[2];
  
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0)
  {
    exit(1);
  }
  // 需要绑定吗       -- 需要的   但是不需要自己显式
  // 那么如何告知
  // 需要监听         --    不需要
  // 需要 asscpt 吗   -- 不要   


  // 那么需要是什么? 发起连接
  struct sockaddr_in server;
  memset(&server, '\0', sizeof(server));


  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  

  close(sock);
  return 0;
}