/**
 * Author       : Qkj
 * Description  :
 * Date         : 2022-11-27 10:39:49
 * LastEditTime : 2022-11-27 10:43:14
 */
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cassert>
#include <iostream>

void Usage(const char *name)
{
  assert(name);
  std::cout << "Usage\n\t" << name << "ip port" << std::endl;
}

// ./a.out ip port
int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    Usage(argv[0]);
    exit(1);
  }
  // 1. 设置命令行设置服务器IP
  std::string ip = argv[1];
  uint16_t port = atoi(argv[2]);
  // 2 创建客户端
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  assert(sockfd > 0);
  // 要不要绑定,为何不需要 不需要绑定,不需要用户自己
  // 这里不需要是指 我们不需要自己手动绑定,OS会帮我们这门做
  // 如果你非要自己干,可以 但是我们严重不推荐
  // 所有的客户端和服务器进行通信的时候,
  // 问题 -- 我们如何让OS自己绑定.为什么呢?客户端很短
  // 为何server要bind.server提供的服务必须被所有人知道 server还不能随便改变
  // 这里我们直接绑定   setto() 会自动
  std::string buffer;
  struct sockaddr_in server;
  int len = sizeof(server);

  bzero(&server, len);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = inet_addr(ip.c_str());
  char inBuffer[1024];
  while (true)
  {
    std::cout << "请输入: ";
    std::getline(std::cin, buffer);
    sendto(sockfd, buffer.c_str(), buffer.size(), 0,
           (struct sockaddr *)&server, len);

    // 收消息
    struct sockaddr_in peer;
    socklen_t peerlen = sizeof(peer);
    bzero(&peer, peerlen);
    memset(inBuffer, '\0', sizeof(inBuffer));
    ssize_t s = recvfrom(sockfd, inBuffer, sizeof(inBuffer) - 1, 0, (struct sockaddr *)&peer, &peerlen);
    if (s > 0)
    {
      inBuffer[s] = '\0';
      std::cout << "server echo#: " << inBuffer << std::endl;
    }
    buffer.clear();
  }

  return 0;
}
