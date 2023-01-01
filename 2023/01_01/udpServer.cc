#include <iostream>
#include <string>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

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
  void start()
  {
  }

private:
  int _socketFd;
};

int main()
{
  // 创建套接字
  // int socket(int domain, int type, int protocol);
  // 本地或者域间 数据包/字节序  协议类型--网络中直接为0
  // 重要的 返回值就是一个文件描述符  -- 就是打开网卡这个文件 -- 我们这么认为,实际是不对的

  // udpServer ser;
  // ser.init();
  // ser.start();
  // 或者PF_INT   数据报 -- udp SOCK_DGRAM
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd < 0)
  {
    cout << strerror(errno) << endl;
    return 0;
  }

  cout << fd << endl;
  return 0;
}