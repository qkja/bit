#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <unistd.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>

static void Usage(std::string name)
{
  std::cout << "Usage:\n\t" << name << " server_ip server_port" << std::endl;
}

// ./udpClient server_ip server_port
// 如果一个客户端要连接server必须知道server对应的ip和port
int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    Usage(argv[0]);
    exit(1);
  }
  // 1. 根据命令行，设置要访问的服务器IP
  std::string server_ip = argv[1];
  uint16_t server_port = atoi(argv[2]);

  // 2. 创建客户端
  // 2.1 创建socket
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  assert(sockfd > 0);

  // 2.2 client 需不需要bind??? 需要bind，但是不需要用户自己bind，而是os自动给你bind
  // 所谓的"不需要"，指的是: 不需要用户自己bind端口信息！因为OS会自动给你绑定，你也最好这么做！
  // 如果我非要自己bind呢？可以！严重不推荐！
  // 所有的客户端软件 <-> 服务器 通信的时候，必须得有 client[ip:port] <-> server[ip:port]
  // 为什么呢？？client很多，不能给客户端bind指定的port，port可能被别的client使用了，你的client就无法启动了
  // 那么server凭什么要bind呢？？server提供的服务，必须被所有人知道！server不能随便改变！
  // 2.2 填写服务器对应的信息

  struct sockaddr_in server;
  bzero(&server, sizeof server);
  server.sin_family = AF_INET;
  server.sin_port = htons(server_port);
  server.sin_addr.s_addr = inet_addr(server_ip.c_str());

  std::string buffer;
  while (true)
  {
    std::cerr << "Please Enter# ";
    std::getline(std::cin, buffer);
    // 发送消息给server
    sendto(sockfd, buffer.c_str(), buffer.size(), 0,
           (const struct sockaddr *)&server, sizeof(server)); // 首次调用sendto函数的时候，我们的client会自动bind自己的ip和port

    // 客户端的消息
    struct sockaddr_in temp;
    socklen_t len = sizeof(temp);
    char outbuffer[1024];
    ssize_t s = recvfrom(sockfd, outbuffer, sizeof(outbuffer), 0, (struct sockaddr *)&temp, &len);
    if (s > 0)
    {
      outbuffer[s] = 0;
      std::cout << "server echo# " << outbuffer << std::endl;
    }
  }

  close(sockfd);

  return 0;
}

