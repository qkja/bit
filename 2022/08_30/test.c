#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
  pid_t id = fork();
  if(id == 0)
  {
    // child
    printf("i am child process\n");
    sleep(5);
  }
  else 
  {
    // parent
    int status = 0;
    pid_t ret = waitpid(id,&status,0);
    if(WIFEXITED(status) && ret > 0)
    {
      printf("子进程的退出信号 %d, coredump标志位 %d,退出码 %d\n",
          status&0x7f,
          (status>>7)&0x1,
          (status>>8)&0xff);
    }
    else 
    {
      printf("非正常退出\n");
    }
  }
  return 0;
}
