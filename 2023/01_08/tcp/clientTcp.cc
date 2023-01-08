#include "util.hpp"
volatile bool quit = false;

static void Usage(char *proc)
{
  std::cerr << "Usage:\n\t" << proc << " port ip" << std::endl;
}

// .clientTcp serverIP, serverPort
int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    Usage(argv[0]);
    exit(USAGE_ERR);
  }

  // 1. 创建套套接字
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
    // 一般我们客户端不带日志
    std::cout << "socket: " << strerror(errno) << std::endl;
    exit(SOCKET_ERR);
  }

  // 2. 需要bind吗  --   前面谈过了,需要,但是不需要自己手动的bind -- 禁止这么干
  // 3. 需要监听吗 --    不需要的 不要自作多情
  // 4. 需要 accept吗 -- 不需要
  // 5. 发起请求 connect
  struct sockaddr_in server;
  socklen_t len = sizeof(server);
  memset(&server, 0, len);
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2]));
  inet_aton(argv[1], &server.sin_addr);

  if (connect(sock, (const struct sockaddr *)&server, len) != 0)
  {
    std::cout << "connect: " << strerror(errno) << std::endl;
    exit(CONNECT_ERR);
  }
  std::cout << "info :connect success... " << sock << std::endl;

  std::string message;
  while (!quit)
  {
    message.clear();
    std::cout << "Please enter# ";
    std::getline(std::cin, message);
    if (strcasecmp(message.c_str(), "quit") == 0)
    {
      quit = true;
      // 我们还要把这个消息写道服务端,让他也退出
    }

    ssize_t s = write(sock, message.c_str(), message.size());
    if (s > 0)
    {
      message.resize(1024);
      // 此时我们进行读
      ssize_t ss = read(sock, (char *)(message.c_str()), message.size() - 1);
      if (ss > 0)
      {
        message[ss] = '\0';
        std::cout << "server echo# " << message << std::endl;
      }
      else
      {
        break;
      }
    }
  }

  close(sock);
  return 0;
}