#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
// 我们再来测试一下
// int execlp(const char *file, const char *arg, ...);
//             找到他            如何执
// 我们执行指令的时候,默认的搜索路径在 PATH　中
// 这里的p 就是PATH 
int main()    
{    
  pid_t id = fork();    
  if(id == 0)    
  {    
    // child    
    // 目前我们执行程序 都是指令  这里我们测试其他的语言,自己的程序
    // int execle(const char *path, const char *arg,
    //              ..., char * const envp[]);


    // execl("/home/bit/104/2022/10_18/mycmd", "mycmd", NULL);
    

    //printf("==============================================\n");

    //execl("./mycmd", "mycmd", NULL);






    //char* const envp[] = {
    //  (char*)"ls",
    //  (char*)"-a",
    //  (char*)"-l",
    //  NULL
    //};
    //execvp("ls", envp);   // 这里的两个 ls 作用是不一样的 
    //execlp("ls", "ls", "-a", "-l", NULL);   // 这里的两个 ls 作用是不一样的 
    // 只要执行这里 就是替换失败    
    exit(1);// 到这里 就是替换失败    
  }    
  // 倒着里一定是父进程的代码    
  int status = 0;    
  int ret = waitpid(id, &status, 0); // 阻塞等待    
  sleep(2);
  if(ret == id)    
  {    
    printf("我是父进程, 等待成功, 退出信号 %d ,退出码 %d\n"    
        , status&0x7f    
      ,(status & 0xff00)>>8);    
  }    
  return 0;    
}    
    


//int main()
//{
//  printf("我是 父进程,pid %d\n", getpid());
//  // 如何使用 见见猪跑
//  // int execl(const char *path, const char *arg, ...);
//  execl("/usr/bin/ls", "ls", "-a", "-l", NULL);
//  printf("我是 父进程,pid %d\n", getpid());
//  return 0;
//}


// 子进程发生程序替换,会影响父进程码 不会 进程具有独立性
// 为什么 ?
// 如何做到的?
// 我们前面说过数据层面发生写时拷贝 fork之后父子进程是代码共享的,
// 要是我们子进程进行程序替换,我这里就不影响父进程了吗
// 首先我们要明白一点付给子 爱要不要 
// 可以理解 代码和数据都发生了写是拷贝

//int main()
//{
//  pid_t id = fork();
//  if(id == 0)
//  {
//    // child
//    execl("/usr/bin/ls", "ls", "-a", "-l", NULL);
//    // 只要执行这里 就是替换失败
//    exit(1);// 到这里 就是替换失败
//  }
//  // 倒着里一定是父进程的代码
//  int status = 0;
//  int ret = waitpid(id, &status, 0); // 阻塞等待
//  if(ret == id)
//  {
//    printf("我是父进程, 等待成功, 退出信号 %d ,退出码 %d\n"
//        , status&0x7f
//      ,(status & 0xff00)>>8);
//  }
//  return 0;
//}
//
//
