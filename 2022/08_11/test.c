#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  pid_t id = fork();
  if(id == 0)
  {
    int cout = 5;
    while(cout)
    {
      printf("我是子进程 ，还存在%d s\n",cout--);
      sleep(1);
    }

    printf("我是一个僵尸进程，等待被回收\n");
    exit(0);
  }
  else 
  {
    while(1)
    {
      printf("我是父进程\n");
      sleep(1);
    }
  }
  return 0;
}
