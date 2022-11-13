/**
* User: Qkj
* Description: 
* Date: 2022-11-12
* Time: 00:00
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
  execl("/usr/bin/ls", "ls", "-a", "-l", NULL);
  return 0;
}





















//int main()
//{
//  pid_t id = fork();
//  if(id == 0)
//  {
//    // child
//    
//    //execl("./mycmd", "mycmd",NULL);
//    char* env[] = {
//     (char*) "MYPATH=YouCanSeeME!!"
//    };
//    execle("./mycmd", "mycmd", NULL,
//        env); // 手动导入环境变量
//    exit(1); // 只要子进程执行这个语句,替换一定失败了
//  }
//
//  // 到这里 一定是父进程  (如果替换成功的话)
//  int status = 0;
//  pid_t ret = waitpid(id, &status, 0);  // 阻塞等待
//
//  sleep(3);
//
//  if(ret == id)
//  {
//    printf("父进程等待成功\n");
//  }
//
//  return 0;
//}




//int main()
//{
//  pid_t id = fork();
//  if(id == 0)
//  {
//    // child
//    
//    // 发生进程替
//    //execl("/home/bit/104/2022/11_12/mycmd", "mycmd",NULL);
//    //execl("./mycmd", "mycmd",NULL);
//    execl("/usr/bin/bash", "bash", "test.sh", NULL);
//    exit(1); // 只要子进程执行这个语句,替换一定失败了
//  }
//
//  // 到这里 一定是父进程  (如果替换成功的话)
//  int status = 0;
//  pid_t ret = waitpid(id, &status, 0);  // 阻塞等待
//
//  sleep(3);
//
//  if(ret == id)
//  {
//    printf("父进程等待成功\n");
//  }
//
//  return 0;
//}











//int main()
//{
//  pid_t id = fork();
//  if(id == 0)
//  {
//    // child
//    
//    // 发生进程替
//    char* argv[] = {(char*)"ls",
//      (char*)"-a", 
//      (char*)"-l",
//      NULL};
//
//    //execlp("ls", "ls", "-a", "-l", NULL);
//    //execl("/usr/bin/ls", "ls", "-a", "-l", NULL);
//    //execv("/usr/bin/ls", argv);
//    execvp("ls", argv);
//    exit(1); // 只要子进程执行这个语句,替换一定失败了
//  }
//
//  int status = 0;
//  pid_t ret = waitpid(id, &status, 0);  // 阻塞等待
//
//  sleep(3);
//
//  if(ret == id)
//  {
//    printf("父进程等待成功\n");
//  }
//  // 到这里 一定是父进程  (如果替换成功的话)
//  return 0;
//}

//int main()
//{
//  printf("我是一个进程, pid %d\n",getpid());
//
//  //execl("/usr/bin/ls","-a","-l", NULL);
//  execl("/usr/bin/aaaaaaaaaa","top", NULL);
//
//  //printf("我执行结束了\n");
//  printf("替换失败\n");  //到这里替换一定失败了
//  return 0;
//}











