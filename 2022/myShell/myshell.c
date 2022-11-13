#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NUM 1024
#define SIZE 128 
#define SEP " "

char command_line[NUM];  // 保存输入的字符串
char* command_args[SIZE];  // 保存分割的字符串
char env_buffer[NUM];
//extern char** environ;
//void PutEnvInMyShell(char* newEnv)
//{
//  putenv(newEnv);
//}

int main()
{
  while(1)
  {
    printf("[zhangsan@主机名 当前路径]# ");

    // 1 输入字符
    memset(command_line, '\0', NUM);
    fgets(command_line, NUM, stdin);

    // a b c \n \0
    command_line[strlen(command_line)-1] = '\0';
    //printf("%s\n",command_line);

    // 2 切割字符
    fflush(stdout);
    command_args[0] = strtok(command_line, SEP);
    int index = 1;

    if(strcmp(command_args[0], "ls") == 0)
    {
      command_args[index++] = (char*)"--color=auto";
    }
    while(command_args[index++] = strtok(NULL, SEP)); // 注意我们是故意写等号的



    if(strcmp(command_args[0], "cd") == 0 && command_args[1] != NULL)
    {
      chdir(command_args[1]);
      continue;
    }
    if(strcmp(command_args[0], "export") == 0 && command_args[1] != NULL)
    {
      // 目前，环境变量信息在command_line,会被清空
      //putenv(command_args[1]); //export myval=100, BUG?
      strcpy(env_buffer, command_args[1]);
      putenv(env_buffer);
      continue;
    }

    pid_t id = fork();

    if(id == 0)
    {
      // child
      // 进程替换
      execvp(command_args[0], command_args);
      exit(1); // 到这一步一定是替换失败
    }

    // 到这里一定是父进程
    int status = 0;
    pid_t ret = waitpid(id, &status, 0);

    if(ret > 0)
    {
      printf("父进程等待成功 sig: %d code %d\n"
         ,status&0x7f
         ,(status>>8)&0xff);
    }


    //for(int i = 0; i < index; i++)
    //{
    //  printf("%d %s\n",i, command_args[i]);
    //}

    //sleep(3);
  }
  return 0;
}















































//#include <stdio.h>
//#include <sys/wait.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <sys/types.h>
//
//#define NUM 1024
//#define SIZE 128
//#define SEP " "
//
//char command_line[NUM];
//char* command_args[SIZE];
//char env_buffer[NUM];
//
//int ChangeDir(char* newPath)
//{
//  chdir(newPath);
//  return 0;
//}
//// 我们导入是一个地址   这里command_arg[1] 每次都更新
//void PutEnvMyShell(char* new_env)
//{
//  putenv(new_env);
//}
//
//int main()
//{
//  // 一个shell本质就是死循环
//  while(1)
//  {
//    printf("[张三@我的主机名 当前目录]# ");
//    fflush(stdout);
//
//    // 获取用户输入
//    // 初始化指定值
//    memset(command_line, '\0', sizeof(command_line) * sizeof(char));
//
//    // 如何获取 用户
//    // ls -1 -a 我们这里是有空格  getline 也可以
//    // 这里我们用 fgets 这里获取的是 NUM - 1个字符  注意这里是C风格的字符串
//    fgets(command_line, NUM, stdin);
//    // 我们回车一下也是 \n 这里的字符串是不可显得,我们要去掉
//    // 这是C语言风格的
//    command_line[strlen(command_line)-1] = '\0';
//    
//    //分割字符串 "ls -a -l"   -- > "ls" "-a" "-l"
//    // 使用一些函数 strtok
//    command_args[0] = strtok(command_line, SEP); // 这里得到 "ls"
//    int index = 1;
//    // 加上一个选项
//    if(strcmp(command_args[0],"ls") == 0)
//      command_args[index++] = (char*)"--color=auto";
//
//    // 注意我们是故意这么写的,不动得看返回值
//    while(command_args[index++] = strtok(NULL, SEP));
//
//    // 到这里分割字符串结束了  
//
//
//
//
//
//    // 这里还面对 一个问题  cd 这个选项  
//    // 原因是 进程具有独立性 是子进程发生了进程替换,我们修改子进程是不会影响父进程的  
//    // 所以这个cd命令不能去发生进程替换 
//    // 我们用的 cd 不是uer/bin的cd 
//    // 这里是一个chdir  更改目录函数
//    if(strcmp(command_args[0], "cd") == 0 && command_args[1] != NULL)
//    {
//      //这里就是 cd 
//      ChangeDir(command_args[1]);
//      continue;
//    }
//
//
//
//    // 这里还是没有导入成功
//    if(strcmp(command_args[0],"export") == 0 && command_args[1] != NULL)
//    {
//      // 我们需要保存 环境变量的内容
//      strcpy(env_buffer, command_args[1]);
//      PutEnvMyShell(env_buffer);
//      //PutEnvMyShell(command_args[1]);
//      continue;
//    }
//
//
//
//
//    //这里我们测试一下
//    //for(int i = 0; i < index; i++)
//    //{
//    //  printf(" %s\n", command_args[i]);
//    //}
//    
//    //TODO
//    //创建子进程去执行
//    pid_t id = fork();
//    if(id == 0)
//    {
//      // child
//      // 选择哪一个
//      // 这里我们使用的PATH里面的 命令
//      execvp(command_args[0], command_args);
//      exit(104);// 只要执行;了,这里替换一定失败了
//    }
//
//    int status = 0;
//    pid_t ret = waitpid(id, &status, 0);
//    if(ret > 0)
//    {
//      //等待成功
//      printf("父进程等待成功 sig: %d code %d\n"
//          ,status&0x7f
//          ,(status>>8)&0xff);
//    }
//    
//  }
//  return 0;
//}
