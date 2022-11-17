#include "comm.h"
using namespace std;

int main()
{

  umask(0);    
  if(mkfifo(IPC_PATH, 0666) == 0)    
  {    
    cerr << "mkfifo error" << endl;    
    return 1;    
  }  
  // 这里我们开始读文件
  int fd = open(IPC_PATH, O_RDONLY);
  if(fd < 0)
  {
    cerr << "open read error" << endl;
    return 0;
  }
#define NUM 1024
  char buffer[NUM];
  while(true)
  {
    memset(buffer, '\0', NUM);
    // 开始读文件
    ssize_t s = read(fd,buffer, NUM-1);
    // abc
    buffer[strlen(buffer)] = '\0';
    if(s > 0)
    {
      printf("客户端-> : %s\n", buffer);
    }
    else if(s == 0)
    {
      printf("客户端退出了,我也退出\n");
      break;
    }
    else 
    {
      assert(NULL);
    }
  }
  close(fd);
  unlink(IPC_PATH);
  return 0;
}
