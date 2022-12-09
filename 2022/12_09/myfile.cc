/**
 * Author       : Qkj
 * Description  :
 * Date         : 2022-12-09 17:41:44
 * LastEditTime : 2022-12-09 17:41:45
 */
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <string>
#include <cstring>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main()
{

  int pipefd[2] = {0};
  pipe(pipefd);

  // 创建子进程
  pid_t id = fork();

  if (id == 0)
  {
    // child 关闭写
    close(pipefd[1]);
#define NUM 100
    char buffer[NUM];
    while (1)
    {
      memset(buffer, '\0', sizeof(buffer));
      ssize_t s = read(pipefd[0], buffer, sizeof(buffer) - 1);
      if (s == 0)
      {
        cout << "读端关闭,我也退出了" << endl;
        break;
      }
      else if (s < 0)
      {
        cout << "读取错误" << endl;
        break;
      }
      else
      {
        buffer[s] = '\0';
        cout << buffer << endl;
        cout << "时间戳是 : " << (uint64_t)time(nullptr) << endl;
      }
    }
    close(pipefd[0]);
    return 0; // 子进程在这里推虎
  }
  else
  {
    // parent 关闭 读
    close(pipefd[0]);

    string msg = "你好子进程.我是父进程";

    int cnt = 0;
    while (cnt < 5)
    {
      write(pipefd[1], msg.c_str(), msg.size());
      cnt++;
      sleep(1);
    }
    cout << "父进程已经接完了" << endl;
    close(pipefd[1]);
  }

  // 等待子进程
  pid_t ret = waitpid(id, NULL, 0);
  if (ret > 0)
  {
    cout << "等待成功" << endl;
  }
  return 0;
}

// int main()
// {
//   int pipefd[2] = {0};
//   if (pipe(pipefd) != 0)
//   {
//     cerr << "pipe open fail" << errno << endl;
//   }
//   // 创建子进程
//   pid_t id = fork();
//   if (id < 0)
//   {
//     // 失败
//   }
//   else if (id == 0)
//   {
//     // child 关闭写
//     close(pipefd[1]);
// #define NUM 100
//     char buffer[NUM];
//     while (1)
//     {
//       memset(buffer, '\0', sizeof(buffer));
//       ssize_t s = read(pipefd[0], buffer, sizeof(buffer) - 1);
//       if (s == 0)
//       {
//         cout << "读端关闭,我也退出了" << endl;
//         break;
//       }
//       else if (s < 0)
//       {
//         cout << "读取错误" << endl;
//         break;
//       }
//       else
//       {
//         buffer[s] = '\0';
//         cout << buffer << endl;
//       }
//     }
//     close(pipefd[0]);
//     return 0; // 子进程在这里推虎
//   }
//   else
//   {
//     // parent 关闭 读
//     close(pipefd[0]);

//     string msg = "你好子进程.我是父进程";
//     int cnt = 0;
//     while (cnt < 5)
//     {
//       write(pipefd[1], msg.c_str(), msg.size());
//       cnt++;
//       sleep(1);
//     }
//     cout << "父进程已经接完了" << endl;
//     close(pipefd[1]);
//   }

//   // 等待子进程
//   pid_t ret = waitpid(id, NULL, 0);
//   if (ret > 0)
//   {
//     cout << "等待成功" << endl;
//   }
//   return 0;
// }

// int main()
// {
//   int pipefd[2] = {0};
//   pipe(pipefd);
//   printf("pipefd[0] %d\n", pipefd[0]);
//   printf("pipefd[1] %d\n", pipefd[1]);
//   return 0;
// }