#include <stdio.h>
#include <unistd.h>

int main()
{

  pid_t id = fork();
  if(id == 0)
  {
    while(1)
    {
      printf("我是子进程\n");
      sleep(1);
    }
  }
  else 
  {
    int count = 5;
    while(count)
    {
      printf("我是父进程\n");
      count--;
      sleep(1);

    }
  }
  return 0;
}

//int main()
//{
//  pid_t id = fork();
//  if(id == 0)
//  {
//    int count = 5;
//    while(count)
//    {
//      printf("我是子进程，还剩下 %d s\n",count--);
//      sleep(1);
//    }
//    printf("我成为了僵尸进程\n");
//  }
//  else
//  {
//    while(1)
//    {
//      printf("我是父进程\n");
//      sleep(1);
//    }
//
//  }
//  return 0;
//}


//int main()
//{
//  pid_t id = fork();
//  if(id == 0)
//  {
//    // child
//    while(1)
//    {
//      printf("我是子进程  pid %d ppid %d\n",getpid(),getppid());
//      
//    }
//  }
//  else 
//  {
//    // parent
//    while(1)
//    {
//      printf("我是父进程  pid %d ppid %d\n",getpid(),getppid());
//      sleep(1);
//    }
//  }
//  return 0;
//} 

