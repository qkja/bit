#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>

void Usage(std::string name)
{
  std::cout << "Usage:\n\t" << name << " serverIp serverPort" << std::endl;
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

  while(true)
  {
    std::cout << "Please enter# ";
    std::getline(std::cin, buffer);
    // 发送消息
    //std::cout << buffer<< std::endl;
    sendto(sockfd, buffer.c_str(), buffer.size(), 0 ,(const struct sockaddr*)&server, len);
  }
  return 0;
}

