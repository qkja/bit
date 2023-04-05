#include "TcpServer.hpp"
#include <memory>
static void usage(std::string str)
{
  std::cerr << "\nUsage: " << str << " port\n"
            << std::endl;
}
/// 这是一个业务层
/// message 一定是一个独立报文
int HandlerRequest(Connection *con, std::string &message)
{
  logMessage(NOTICE, "获取了 %s inbuffer %s", message.c_str(), con->inbuffer.c_str());
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    usage(argv[0]);
    exit(1);
  }

  int port = atoi(argv[1]);

  std::unique_ptr<TcpServer> svr(new TcpServer(HandlerRequest, port));
  svr->Run();
  return 0;
}