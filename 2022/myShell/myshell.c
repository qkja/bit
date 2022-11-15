#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <ctype.h>

#define SEP " "
#define NUM 1024
#define SIZE 128

#define DROP_SPACE(s) do { while(isspace(*s)) s++; }while(0)

char command_line[NUM];
char *command_args[SIZE];

char env_buffer[NUM]; //for test

#define NONE_REDIR  -1
#define INPUT_REDIR  0
#define OUTPUT_REDIR 1
#define APPEND_REDIR 2

int g_redir_flag = NONE_REDIR;
char *g_redir_filename = NULL;

extern char**environ;

//对应上层的内建命令
int ChangeDir(const char * new_path)
{
    chdir(new_path);

    return 0; // 调用成功
}

void PutEnvInMyShell(char * new_env)
{
    putenv(new_env);
}

void CheckDir(char *commands)
{
    assert(commands);
    //[start, end)
    char *start = commands;
    char *end = commands + strlen(commands);
    // ls -a -l
    while(start < end)
    {
        if(*start == '>')
        {
            if(*(start+1) == '>')
            {
                //ls -a -l>>  log.txt --追加
                *start = '\0';
                start += 2;
                g_redir_flag = APPEND_REDIR;
                DROP_SPACE(start);
                g_redir_filename = start;
                break;
            }
            else{
                //ls -a -l > log.txt -- 输出重定向
                *start = '\0';
                start++;
                DROP_SPACE(start);
                g_redir_flag = OUTPUT_REDIR;
                g_redir_filename = start;
                break;
            }
        }
        else if(*start == '<')
        {
            // 输入重定向
            *start = '\0';
            start++;
            DROP_SPACE(start);
            g_redir_flag = INPUT_REDIR;
            g_redir_filename = start;
            break;
        }
        else 
        {
            start++;
        }
    }
}

int main()
{
    //shell 本质上就是一个死循环
    while(1)
    {
        g_redir_flag = NONE_REDIR;
        g_redir_filename = NULL;

        //不关心获取这些属性的接口, 搜索一下
        //1. 显示提示符
        printf("[张三@我的主机名 当前目录]# ");
        fflush(stdout);

        //2. 获取用户输入
        memset(command_line, '\0', sizeof(command_line)*sizeof(char));
        fgets(command_line, NUM, stdin); //键盘，标准输入，stdin, 获取到的是c风格的字符串, '\0'
        command_line[strlen(command_line) - 1] = '\0';// 清空\n

        //2.1 ls -a -l>log.txt or cat<file.txt or ls -a -l>>log.txt or ls -a -l
        // ls -a -l>log.txt -> ls -a -l\0log.txt
        CheckDir(command_line);

        //3. "ls -a -l -i" -> "ls" "-a" "-l" "-i" 字符串切分
        command_args[0] = strtok(command_line, SEP);
        int index = 1;
        // 给ls命令添加颜色
        if(strcmp(command_args[0]/*程序名*/, "ls") == 0 ) 
            command_args[index++] = (char*)"--color=auto";
        // = 是故意这么写的
        // strtok 截取成功，返回字符串其实地址
        // 截取失败，返回NULL
        while(command_args[index++] = strtok(NULL, SEP));

        //for debug
        //for(int i = 0 ; i < index; i++)
        //{
        //    printf("%d : %s\n", i, command_args[i]);
        //}
    
        // 4. TODO, 编写后面的逻辑, 内建命令
        if(strcmp(command_args[0], "cd") == 0 && command_args[1] != NULL)
        {
            ChangeDir(command_args[1]); //让调用方进行路径切换, 父进程
            continue;
        }
        if(strcmp(command_args[0], "export") == 0 && command_args[1] != NULL)
        {
            // 目前，环境变量信息在command_line,会被清空
            // 此处我们需要自己保存一下环境变量内容
            strcpy(env_buffer, command_args[1]);
            PutEnvInMyShell(env_buffer); //export myval=100, BUG?
            continue;
        }

        // 5. 创建进程,执行
        pid_t id = fork();
        if(id == 0)
        {
            int fd = -1;
            switch(g_redir_flag)
            {
                case NONE_REDIR:
                    break;
                case INPUT_REDIR:
                    fd = open(g_redir_filename, O_RDONLY);
                    dup2(fd, 0);
                    break;
                case OUTPUT_REDIR:
                    fd = open(g_redir_filename, O_WRONLY | O_CREAT | O_TRUNC);
                    dup2(fd, 1);
                    break;
                case APPEND_REDIR:
                    fd = open(g_redir_filename, O_WRONLY | O_CREAT | O_APPEND);
                    dup2(fd, 1);
                    break;
                default:
                    printf("Bug?\n");
                    break;
            }
            //child
            // 6. 程序替换, 会影响曾经子进程打开的文件吗？不影响
            //exec*?
            execvp(command_args[0]/*不就是保存的是我们要执行的程序名字吗？*/, command_args);
            exit(1); //执行到这里，子进程一定替换失败
        }
        int status = 0;
        pid_t ret = waitpid(id, &status, 0);
        if(ret > 0)
        {
            printf("等待子进程成功: sig: %d, code: %d\n", status&0x7F, (status>>8)&0xFF);
        }
    }// end while
}






//#include <stdio.h>
//#include <ctype.h>
//#include <unistd.h>
//#include <string.h>
//#include <assert.h>
//#include <stdlib.h>
//#include <sys/wait.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//#include <sys/types.h>
//
//#define NUM 1024
//#define SIZE 128 
//#define SEP " "
//
//#define NONE_REDIR -1
//#define INPUT_REDIR 0
//#define OUTPUT_REDIR 1
//#define APPPUT_REDIR 2
//
//int g_redir_flags = NONE_REDIR;
//char* g_redir_filename = NULL;
//
//#define DROP_SPACE(s) do { while(isspace(*s)) s++;}while(0)
//
//
//char command_line[NUM];  // 保存输入的字符串
//char* command_args[SIZE];  // 保存分割的字符串
//char env_buffer[NUM];
//
//void CheckDir(char* p)
//{
//  //printf("你调用这个函数了吗\n");
//  assert(p);
//  char* start = p;
//  char* end = p+strlen(p); // end 指向 \0
//  // ls -a -l > log.txt
//  while(start < end)
//  {
//    if(*start == '>')
//    {
//      if(start +1 < end && *(start+1) == '>')
//      {
//        // 追加 重定向
//        *start = '\0';
//        start += 2;
//
//        g_redir_flags = APPPUT_REDIR;
//        DROP_SPACE(start);
//        g_redir_filename = start; // 处理一下空格
//      }
//      else 
//      {
//        //printf("=============\n");
//        // 输出重定向 
//        *start = '\0';
//        start++;
//        DROP_SPACE(start);
//        g_redir_flags = OUTPUT_REDIR;
//        g_redir_filename = start; // 处理一下空格
//      //printf("%d\n",g_redir_flags);
//      }
//      break;
//      // 其他的都不考虑 这不是我们应该做的 用户什么都可能做
//    }
//    else if(*start == '<')
//    {
//      *start = '\0';
//      start++;
//      DROP_SPACE(start);
//
//      g_redir_flags = INPUT_REDIR;
//      g_redir_filename = start; // 处理一下空格
//
//      break;
//    }
//    else 
//    {
//      ++start;
//    }
//  } // end of while
//}
//
//int main()
//{
//  while(1)
//  {
//    g_redir_flags = NONE_REDIR;
//    g_redir_filename = NULL;
//    printf("[zhangsan@主机名 当前路径]# ");
//
//    fflush(stdout);
//    // 1 输入字符
//    memset(command_line, '\0', NUM);
//    fgets(command_line, NUM, stdin);
//
//    // a b c \n \0
//    command_line[strlen(command_line)-1] = '\0';
//    //printf("%s\n",command_line);
//
//    // 2 切割字符
//    command_args[0] = strtok(command_line, SEP);
//    int index = 1;
//
//    // ls -a -l >log.txt
//    // 判断是否冲重定向  这里只谈  输出>
//    
//    // ls -a -l /0log.txt
//    CheckDir(command_line);
//
//    if(strcmp(command_args[0], "ls") == 0)
//    {
//      command_args[index++] = (char*)"--color=auto";
//    }
//    while(command_args[index++] = strtok(NULL, SEP)); // 注意我们是故意写等号的
//
//    if(strcmp(command_args[0], "cd") == 0 && command_args[1] != NULL)
//    {
//      chdir(command_args[1]);
//      continue;
//    }
//    if(strcmp(command_args[0], "export") == 0 && command_args[1] != NULL)
//    {
//      // 目前，环境变量信息在command_line,会被清空
//      //putenv(command_args[1]); //export myval=100, BUG?
//      strcpy(env_buffer, command_args[1]);
//      putenv(env_buffer);
//      continue;
//    }
//    
//
//    pid_t id = fork();
//
//    if(id == 0)
//    {
//      int fd = -1;
//      switch(g_redir_flags)
//      {
//     // printf("是不是正确的\n");
//        case NONE_REDIR:
//          break;
//        case INPUT_REDIR:
//          fd = open(g_redir_filename, O_RDONLY, 0666);
//          dup2(fd, 0);
//          break;
//        case OUTPUT_REDIR:
//          fd = open(g_redir_filename, O_WRONLY | O_CREAT | O_TRUNC,0666);
//          dup2(fd, 1);
//          break;
//        case APPPUT_REDIR:
//          fd = open(g_redir_filename, O_WRONLY | O_CREAT | O_APPEND,0666);
//          dup2(fd, 1);
//          break;
//        default:
//          printf("错误\n");
//          break;
//      }
//
//      //printf("%d\n",g_redir_flags);
//      //printf("%d\n",fd);
//      // child
//      // 进程替换   程序替换会影响 打开文件  吗  不会,文件属于PCB结构，所以不会
//      
//
//      
//      execvp(command_args[0], command_args);
//      exit(1); // 到这一步一定是替换失败
//    }
//
//    // 到这里一定是父进程
//    int status = 0;
//    pid_t ret = waitpid(id, &status, 0);
//
//    if(ret > 0)
//    {
//      printf("父进程等待成功 sig: %d code %d\n"
//         ,status&0x7f
//         ,(status>>8)&0xff);
//    }
//
//
//    //for(int i = 0; i < index; i++)
//    //{
//    //  printf("%d %s\n",i, command_args[i]);
//    //}
//
//    //sleep(3);
//  }
//  return 0;
//}

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
