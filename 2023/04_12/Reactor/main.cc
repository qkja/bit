#include "TcpServer.hpp"
#include "Service.hpp"
#include <memory>
static void usage(std::string str)
{
  std::cerr << "\nUsage: " << str << " port\n"
            << std::endl;
}
/// 这是一个业务层
/// message 一定是一个独立报文
int HandlerRequestHelper(Connection *con, std::string &message, service_t func)
{
  std::cout << "获取报文 request: " << message << "inbuffer : " << con->inbuffer << std::endl;
  std::cout << "处理业务....." << std::endl;
  struct Request rep;
  if (!Parser(message, &rep))
  {
    // 直接异常
    // con->_excepter(con);
    return -1;
  }

  // 处理数据 -- 业务处理
  struct Response rsp = func(rep);
  // 序列化
  std::string sender;
  Serialize(rsp, &sender);
  con->outbuffer += sender;
  con->_sender(con);
  // 这里是ET模式
  if (con->outbuffer.empty())
    con->R->EnableReadWrite(con->_sock, true, false);
  else
    con->R->EnableReadWrite(con->_sock, true, true);

  // 这里是LT模式
  // con->R->EnableReadWrite(con->_sock, true, true);
}
int HandlerRequest(Connection *con, std::string &message)
{
  return HandlerRequestHelper(con, message, calculator);
  // logMessage(NOTICE, "获取了 %s inbuffer %s", message.c_str(), con->inbuffer.c_str());
  // logMessage(NOTICE, "获取了 %s", message.c_str());

  /// message 一定是一个独立报文, 因此我们需要进行反序列化

    return 0;
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