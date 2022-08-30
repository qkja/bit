#include <stdio.h>
#include <unistd.h>

int main()
{
  pid_t id = fork();
  while(1)
  {
    if( id == 0 )
    {
      // child
      printf("我是子进程 pid ：%d ppid : %d\n",getpid(),getppid());
      sleep(1);
    }
    else 
    {
      // parent
      printf("我是父进程 pid ：%d ppid : %d\n",getpid(),getppid());
      sleep(1);

    }
  }
  return 0;
}
