#include "EpollServer.hpp"
#include <memory>
static void usage(std::string str)
{
  std::cerr << "\nUsage: " << str << " port\n"
            << std::endl;
}

int func(int sock)
{
  // 那么这里直接读 bug
  char buffer[1024] = {0};

  ssize_t s = recv(sock, buffer, sizeof(buffer) - 1, 0);
  if (s > 0)
  {
    buffer[s] = '\0';
    // std::cout << buffer << std::endl;
    logMessage(NOTICE, "client[%d]# %s", sock, buffer);
  }
  return s;
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    usage(argv[0]);
    exit(1);
  }

  int port = atoi(argv[1]);

  std::unique_ptr<EpollServer> epollserver(new EpollServer(port, func));
  epollserver->InitEpollServer();
  epollserver->Run();
  return 0;
}
