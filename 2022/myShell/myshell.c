#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define NUM 1024
#define SIZE 128
#define SEP " "

char command_line[NUM];
char* command_args[SIZE];

int main()
{
  // 一个shell本质就是死循环
  while(1)
  {
    printf("[张三@我的主机名 当前目录]# ");
    fflush(stdout);

    // 获取用户输入
    // 初始化指定值
    memset(command_line, '\0', sizeof(command_line) * sizeof(char));

    // 如何获取 用户
    // ls -1 -a 我们这里是有空格  getline 也可以
    // 这里我们用 fgets 这里获取的是 NUM - 1个字符  注意这里是C风格的字符串
    fgets(command_line, NUM, stdin);
    // 我们回车一下也是 \n 这里的字符串是不可显得,我们要去掉
    command_line[strlen(command_line)-1] = '\0';
    
    //分割字符串 "ls -a -l"   -- > "ls" "-a" "-l"
    // 使用一些函数 strtok
    command_args[0] = strtok(command_line, SEP); // 这里得到 "ls"
    int index = 1;
    // 注意我们是故意这么写的,不动得看返回值
    while(command_args[index++] = strtok(NULL, SEP));
    
    //这里我们测试一下
    //for(int i = 0; i < index; i++)
    //{
    //  printf(" %s\n", command_args[i]);
    //}
    
    //TODO
    //创建子进程去执行
    pid_t id = fork();
    if(id == 0)
    {
      // child
      // 选择哪一个
      execvp(command_args[0], command_args);
      exit(104);// 只要执行;了,这里替换一定失败了
    }
    int status = 0;
    pid_t ret = waitpid(id, &status, 0);
    if(ret > 0)
    {
      //等待成功
      printf("父进程等待成功 sig: %d code %d\n"
          ,status&0x7f
          ,(status>>8)&0xff);
    }
    
  }
  return 0;
}
