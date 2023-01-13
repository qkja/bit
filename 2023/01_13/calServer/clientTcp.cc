#include "util.hpp"
#include "Protocol.hpp"
#include <cstdio>
// 2. 需要bind吗？？需要，但是不需要自己显示的bind！ 不要自己bind！！！！
// 3. 需要listen吗？不需要的！
// 4. 需要accept吗？不需要的!

volatile bool quit = false;

static void Usage(std::string proc)
{
  std::cerr << "Usage:\n\t" << proc << " serverIp serverPort" << std::endl;
  std::cerr << "Example:\n\t" << proc << " 127.0.0.1 8081\n"
            << std::endl;
}
// ./clientTcp serverIp serverPort
int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    Usage(argv[0]);
    exit(USAGE_ERR);
  }
  std::string serverIp = argv[1];
  uint16_t serverPort = atoi(argv[2]);

  // 1. 创建socket SOCK_STREAM
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
    std::cerr << "socket: " << strerror(errno) << std::endl;
    exit(SOCKET_ERR);
  }

  // 2. connect，发起链接请求，你想谁发起请求呢？？当然是向服务器发起请求喽
  // 2.1 先填充需要连接的远端主机的基本信息
  struct sockaddr_in server;
  memset(&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(serverPort);
  inet_aton(serverIp.c_str(), &server.sin_addr);
  // 2.2 发起请求，connect 会自动帮我们进行bind！
  if (connect(sock, (const struct sockaddr *)&server, sizeof(server)) != 0)
  {
    std::cerr << "connect: " << strerror(errno) << std::endl;
    exit(CONN_ERR);
  }
  std::cout << "info : connect success: " << sock << std::endl;

  std::string message;
  while (!quit)
  {
    message.clear();
    std::cout << "请输入表达式>>> "; // 1 + 1
    std::getline(std::cin, message); // 结尾不会有\n
    if (strcasecmp(message.c_str(), "quit") == 0)
    {
      quit = true;
      continue;
    }

    Request req;
    std::string package;
    req.serialize(&package); // 1 + 1
    package = encode(package, package.size());
    ssize_t s = write(sock, package.c_str(), package.size());
    if (s > 0)
    {
      char buff[1024];
      size_t s = read(sock, buff, sizeof(buff) - 1);
      if (s > 0)
        buff[s] = 0;
      std::string echoPackage = buff;
      Response resp;
      uint32_t len = 0;
      std::string tmp = decode(echoPackage, &len);
      if (len > 0)
      {
        echoPackage = tmp;
        resp.deserialize(echoPackage);
        printf("[exitcode: %d] %d\n", resp.exitCode_, resp.result_);
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