// 问题 为何 子进程加入sleep之后  才可以跑
// 否则一直死循环
// 多进程如何调试

//#include <iostream>
//#include <vector>
//#include <stdio.h>
//#include <unistd.h>
//#include <stdlib.h>
//#include <sys/types.h>
//#include <sys/wait.h>
//
//typedef void (*handler_t)();
//
////方法集
//std::vector<handler_t> handlers;
//
//void fun1()
//{
//    printf("hello, 我是方法1\n");
//}
//void fun2()
//{
//    printf("hello, 我是方法2\n");
//}
//
//void Load()
//{
//    //加载方法
//    handlers.push_back(fun1);
//    handlers.push_back(fun2);
//}
//
//int main()
//{
//    pid_t id = fork();
//    if(id == 0)
//    {
//        //子进程
//        int count = 0;
//        while(1)
//        {
//            printf("我是子进程, 我的PID: %d, 我的PPID:%d\n", getpid(), getppid());
//            sleep(1);
//            count++;
//            if(count == 10)
//            {
//              break;
//            }
//        }
//        exit(104);
//    }
//    else if(id > 0)
//    {
//        //父进程
//        // 基于非阻塞的轮询等待方案
//        int status = 0;
//        while(1)
//        {
//            pid_t ret = waitpid(-1, &status, WNOHANG);
//            if(ret > 0)
//            {
//                printf("等待成功, %d, exit sig: %d, exit code: %d\n", ret, status&0x7F, (status>>8)&0xFF);
//                break;
//            }
//            else if(ret == 0)
//            {
//                //等待成功了，但是子进程没有退出
//                printf("子进程好了没，奥， 还没，那么我父进程就做其他事情啦...\n");
//                if(handlers.empty()) Load();
//                for(auto f : handlers)
//                {
//                    f(); //回调处理对应的任务
//                }
//
//                sleep(1);
//            }
//            else{
//                //出错了，暂时不处理
//            }
//        }
//    }
//    else{
//        //do nothing
//    }
//}
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>
#include <iostream>
#include <vector>
// 加载函数 指针
typedef void (* handler_t)();
// 方法集
std::vector<handler_t> handlers;
void func1()
{
  printf("hello 我是func1\n");
}
void func2()
{
  printf("hello 我是func2\n");
}

// 这里我们添加一个 load 函数
// 加载方法
void Load()
{
  handlers.push_back(func1);
  handlers.push_back(func2);
}

//#include <stdio.h>    
//#include <stdlib.h>    
//#include <sys/wait.h>    
//#include <unistd.h>    
//#include <assert.h>    
//#include <iostream>    
//int main()    
//{    
//    
//  pid_t id = fork();    
//  if(id == 0)    
//  {    
//    int count = 0;    
//    while(1)    
//    {    
//      printf("我是子进程 pid: %d\n", getpid());    
//      sleep(1);    
//      count++;    
//      if(count == 5)    
//      {    
//        break;    
//      }    
//    }    
//    exit(104);     
//  }    
//  else if (id > 0)    
//  {    
//    int status = 0;    
//    // 等待 子进程    
//    while(1)    
//    {    
//    
//      pid_t waitPid = waitpid(id, &status, WNOHANG);    
//      if(waitPid > 0)    
//      {    
//        printf("我是父进程,我已经等待成功了\n");    
//        // 这里查看进程的退出信号 和 退出码    
//        if(WIFEXITED(status))    
//        {    
//          // 到这里进程正常退出    
//          printf("子进程正常退出 退出码 %d 退出信号 %d\n"    
//              ,(status & 0xff00)>>8    
//              , status&0x7f);    
//        }    
//        else    
//        {    
//          // 进程非正常退出    
//          printf("子进程异常退出 退出码 %d 退出信号 %d\n"    
//              ,(status & 0xff00)>>8    
//              , status&0x7f);    
//        }    
//        break;    
//      }    
//      else if(waitPid == 0)    
//      {    
//        // 到这里 父进程 等待成功了,但是子进程还没有退出    
//        printf("我是父进程,子进程你好了没,还没有,那我忙自己的事了\n");    
//        sleep(1);  
//      }    
//      else                                                                                                 
//      {    
//        // 这里 等待失败 先暂时什么都不做    
//        assert(NULL);    
//      }    
//    }    
//  }    
//  else    
//  {    
//    printf("创建进程失败!!!\n");    
//  }    
//  return 0;    
//}  

int main()
{

  pid_t id = fork();
  if(id == 0)
  {
    // child
    //while(1)
    //{
    //  printf("我是子进程 pid: %d\n", getpid());
    //  sleep(1);
    //}
    int count = 0;
    while(1)
    {
      printf("我是子进程 pid: %d\n", getpid());
      //sleep(1);
      count++;
      //std::cout << count << std::endl;
      if(count == 5)
      {
        break;
      }
      sleep(1);
    }
    //exit(104);
    return 100;
  }
  else if (id > 0)
  {
    int status = 0;
    // 等待 子进程
    while(1)
    {

      pid_t waitPid = waitpid(id, &status, WNOHANG);
      if(waitPid > 0)
      {
        printf("我是父进程,我已经等待成功了\n");
        // 这里查看进程的退出信号 和 退出码
        if(WIFEXITED(status))
        {
          // 到这里进程正常退出
          printf("子进程正常退出 退出码 %d 退出信号 %d\n"
              ,(status & 0xff00)>>8
              , status&0x7f);
        }
        else 
        {
          // 进程非正常退出
          printf("子进程异常退出 退出码 %d 退出信号 %d\n"
              ,(status & 0xff00)>>8
              , status&0x7f);
        }
        break;
      }
      else if(waitPid == 0)
      {
        // 到这里 父进程 等待成功了,但是子进程还没有退出
        printf("我是父进程,子进程你好了没,还没有,那我忙自己的事了\n");
        // 如何然父进程忙自己的事
        if(handlers.empty())
          Load(); // 记载一批方法
        sleep(1);
        for(auto ptr : handlers)
        {
          ptr();
        }
        
        //sleep(1);
      }
      else 
      {
        // 这里 等待失败 先暂时什么都不做
        assert(NULL);
      }
    }
  }
  else 
  {
    printf("创建进程失败!!!\n");
  }
  return 0;
}
