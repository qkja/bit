#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/socket.h>
#include <assert.h>

void Usage(std::string name)
{
  std::cout << "Usage:\n\t" << name << " serverIp serverPort" << std::endl;
}

void *recverRead(void *args)
{
  pthread_detach(pthread_self());
  int sockfd = *(int *)args;
  // 收回转到的消息
  char outbuffer[1024] = {0};
  struct sockaddr_in ret;
  socklen_t len = sizeof(ret);
  while (true)
  {
    ssize_t s = recvfrom(sockfd, outbuffer, sizeof(outbuffer) - 1, 0,
                         (struct sockaddr *)&ret, &len);
    // sleep(5);
    if (s > 0)
    {
      outbuffer[s] = '\0';
      std::cout << "server echo# " << outbuffer << std::endl;
    }
  }
}

// udpClient serverIp serverPort
int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    Usage(argv[0]);
    exit(1);
  }
  // 获取 服务器IP
  std::string serverIP = argv[1];
  uint16_t serverPort = atoi(argv[2]);
  // 创建客户端
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  assert(sockfd >= 0);
  std::string buffer;

  struct sockaddr_in server;
  int len = sizeof(server);
  bzero(&server, len);

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(serverIP.c_str());
  server.sin_port = htons(serverPort);
  pthread_t t;
  pthread_create(&t, nullptr, recverRead, (void *)&sockfd);
  while (true)
  {
    std::cerr << "Please enter# ";
    std::getline(std::cin, buffer);
    // 发送消息
    // std::cout << buffer<< std::endl;
    sendto(sockfd, buffer.c_str(), buffer.size(), 0, (const struct sockaddr *)&server, len);
    // 此时有点问题,消息路由的时候我们被卡住了,我们希望可以出现一个线程负责读
  }
  return 0;
}
