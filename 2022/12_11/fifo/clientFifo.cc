/**
 * Author       : Qkj
 * Description  : 写入文件
 * Date         : 2022-12-11 14:01:51
 * LastEditTime : 2022-12-11 14:14:18
 */
#include "comm.h"

int main()
{
  int fd = open(IPC_PATH, O_WRONLY);
  if (fd < 0)
  {
    std::cerr << "open : " << errno << std::endl;
    return 1;
  }
#define NUM 1024
  char line[NUM];
  while (true)
  {
    std::cout << "请输入你的消息: ";
    fflush(stdout);
    memset(line, '\0', sizeof(line));

    if (fgets(line, sizeof(line) - 1, stdin) != NULL)
    {
      // fgets 读取是    abc\n\0  会自动添加'\0' -- C语言接口

      line[strlen(line) - 1] = '\0';
      write(fd, line, strlen(line));
    }
    else
    {
      break;
    }
  }
  close(fd);
  std::cout << "客户端退出了" << std::endl;

  return 0;
}
