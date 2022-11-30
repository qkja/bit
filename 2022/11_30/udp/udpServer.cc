/**
 * Author       : Qkj
 * Description  : udp套接字
 * Date         : 2022-11-27 10:39:59
 * LastEditTime : 2022-11-27 10:43:20
 */
#include <sys/types.h>
#include <sys/socket.h>

class udpServer
{
public:
  udpServer()
  {
  }
  ~udpServer()
  {
  }

public:
void start(){};
void init(){};
private:
int _sockfd;
};

// 域间套接字  -- 一个主机内通信
//
int main()
{
  //int fd = socket(A)
  return 0;
}
