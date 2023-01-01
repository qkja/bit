#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <iostream>
#include <string>
using namespace std;

class udpServer
{
public:
  udpServer(/* args */);
  ~udpServer();

public:
  void init()
  {
  }

private:
  /* data */
};

int main()
{
  // 创建套接字
  // int socket(int domain, int type, int protocol);
  // 本地或者域间 数据包/字节序  协议类型--网络中直接为0


  udpServer ser;
  ser.init();
  return 0;
}