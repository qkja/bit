#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  pid_t id = fork();
  if(id == 0)
  {
    int count = 1;
    while(1)
    {
      printf("我是子进程 pid %d\n",getpid());
      sleep(1);
      count++;
      if(count == 15)
      {
       break;
      }
    }
    
    //  这里我们使用 也指针
    printf("注意,我们要使用 野指针了\n");
    int* p = NULL;
    *p = 10;
  }
  else 
  {
    int statu = 0;
    printf("我是父进程,在等待子进程结束\n");
    pid_t ret = waitpid(id,&statu,0);
    if(ret > 0)
    {
      if(WIFEXITED(statu))
      {
        printf("子进程退出码 %d\n",WEXITSTATUS(statu));
      }
      else 
      {
        printf("进程非正常退出\n");
      }
    }
    else 
    {
      printf("等待失败\n");
    }
  }
  return 0;
}




//int main()
//{
//  pid_t id = fork();
//  if(id == 0)
//  {
//    //child
//    while(1)
//    {
//      printf("我是子进程 pid %d\n",getpid());
//      sleep(1);
//    }
//  }
//  else 
//  {
//    printf("我是父进程,正在等待子进程 pid %d\n",getpid());
//    sleep(20);
//    pid_t ret = wait(NULL);
//    sleep(20);
//    if(ret == -1)
//    {
//      printf("等待错误\n");
//    }
//    else 
//    {
//      printf("等待成功\n");
//    }
//  }
//  return 0;
//}
//
//int main()
//{
//  pid_t id = fork();
//  if(id == 0)
//  {
//    int cout = 5;
//    while(cout)
//    {
//      printf("我是子进程 ，还存在%d s\n",cout--);
//      sleep(1);
//    }
//
//    printf("我是一个僵尸进程，等待被回收\n");                                                          
//    exit(0);
//  }
//  else
//  {
//    while(1)
//    {
//      printf("我是父进程\n");
//      sleep(1);
//    }
//  }
//  return 0;
//}


//int main()
//{
//  pid_t id = fork();
//  if(id > 0)
//  {
//    printf("我是子进程\n");
//    exit(111);
//  }
//  else 
//  {
//    printf("我是父进程\n");
//  }
//  return 0;
//}
//

//int count = 0;
//int main()
//{
//  while(1)
//  {
//    pid_t id = fork();
//    if(id < 0)
//    {
//      printf("进程创建失败 %d\n",count);
//      break;
//    }
//    else if(id == 0) 
//    {
//      printf("我是子进程 %d\n",getpid());
//      sleep(2);
//      exit(0);
//    }
//    ++count;
//  }
//  return 0;
//}
//
//
//









//{
//  printf("hello word");
//  _exit(111);
//}
//int main()
//{
//  func();
//  return 0;
//}

//int main()
//{
//  int n = 50;
//  for(int i=0;i<n;i++)
//  {
//    printf("%d %s\n",i,strerror(i));
//  }
//  return 1;
//}
