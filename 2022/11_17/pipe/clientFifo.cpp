/**
* User: Qkj
* Description: 
* Date: 2022-11-17
* Time: 10:00
*/
#include "comm.h"
using namespace std;
// 我们要做的是 使用命名管道
// 这里的命名管道本质和匿名一样,没有在银盘上创建实际的文件,只是提供一个通道而已

int main()
{

  // 本质就是看到通一份资源 匿名是通过继承做到的,
  // 命名是通过管道文件所在的路径做到的
  //int mkfifo(const char *pathname, mode_t mode);
  //参数  路径 , 权限


  // 开始通信
  int fd = open(IPC_PATH, O_WRONLY);
  if(fd < 0)
  {
    return 2;
  }

  // 写文件
#define NUM 1024
  char buffer[NUM];
  while(true)
  {
    memset(buffer, '\0', NUM);
    printf("请输入: ");
    fflush(stdout);

    if(fgets(buffer,NUM, stdin) != nullptr)
    {
      // abc\n
      buffer[strlen(buffer)-1] = '\0';
      write(fd,buffer, strlen(buffer));
    }
    else 
    {
      break;
    }
  }
  close(fd);
  return 0;
}
