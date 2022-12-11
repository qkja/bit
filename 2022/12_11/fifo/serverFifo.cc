/**
 * Author       : Qkj
 * Description  : 制作命名管道文件 + 读取文件
 * Date         : 2022-12-11 14:01:37
 * LastEditTime : 2022-12-11 14:17:11
 */
#include "comm.h"

int main()
{
  umask(0);
  if (mkfifo(IPC_PATH, 0666) < 0)
  {
    std::cerr << "mkfifo errno " << errno << std::endl;
    return 1;
  }
  int fd = open(IPC_PATH, O_RDONLY);
  if (fd < 0)
  {
    std::cerr << "openerrno " << errno << std::endl;
    return 2;
  }
// 正常的通信过程
#define NUM 1024
  char buffer[NUM];
  while (true)
  {
    memset(buffer, '\0', sizeof(buffer));

    // 开始读
    ssize_t s = read(fd, buffer, sizeof(buffer) - 1);

    if (s == 0)
    {
      std::cout << "客户端推出了,我也推出了" << std::endl;
      break;
    }
    else if (s > 0)
    {
      buffer[s] = '\0';
      std::cout << "客户端发送了一条信息 -> " << buffer
                << std::endl;
    }
    else
    {
      assert(0);
    }
  }

  close(fd);
  std::cout << "服务端退出了" << std::endl;
  return 0;
}
