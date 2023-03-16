/**
 * User: Qkj
 * Description:
 * Date: 2023-03-15
 * Time: 10:05
 */
#include <iostream>
#include <unistd.h>
#include <error.h>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <stdlib.h>
using namespace std;

#define PATH_NAME "/home/bit/104/2022/12_12"
#define PROJ_ID 0x14
#define MEM_SIZE 4096
int flags = IPC_CREAT | IPC_EXCL;

int main()
{
  umask(0);

  key_t key = ftok(PATH_NAME, PROJ_ID);

  int shmid = shmget(key, MEM_SIZE, flags | 0666);
  char *str = (char *)shmat(shmid, nullptr, 0); // 0 默认读写
  while (1)
  {
    cout << str << endl;
  }

  // 去关联
  shmdt(str);
  shmctl(shmid, IPC_RMID, nullptr);
  return 0;
}

// #define FILE_PATH ".fifo"
// // 服务端
// int main()
// {
//   umask(0);
//   mkfifo(FILE_PATH, 0666);
//   // 打开文件
//   int fd = open(FILE_PATH, O_RDONLY);
//   char buffer[1024];
//   memset(buffer, '\0', sizeof(buffer));
//   ssize_t s = read(fd, buffer, sizeof(buffer)-1);
//   // 开始读
//   buffer[s] = '\0';
//   cout << buffer << endl;
//   return 0;
// }

// int main()
// {
//   int pipeFd[2] = {0};
//   if (-1 == pipe(pipeFd))
//   {
//     cerr << strerror(errno) << endl;
//   }

//   pid_t id = fork();
//   if (id == -1)
//   {
//     cerr << strerror(errno) << endl;
//   }

//   if (id == 0)
//   {
//     close(pipeFd[1]); // 关闭写端
//     char buffer[1024];

//     while (1)
//     {
//       memset(buffer, '\0', sizeof(buffer));
//       ssize_t s = read(pipeFd[0], buffer, sizeof(buffer) - 1);
//       if (s > 0)
//       {
//         buffer[s] = '\0';
//         cout << buffer << endl;
//       }
//       else if (s == 0)
//       {
//         break;
//       }
//       else
//       {
//         // donothing
//       }
//     }
//     close(pipeFd[0]);
//     exit(0);
//   }

//   // 到这一定是父进程
//   close(pipeFd[0]);
//   string str = "i am father";
//   write(pipeFd[1], str.c_str(), str.size());

//   close(pipeFd[1]); // 要先关闭,后等待
//   waitpid(id, nullptr, 0);
//   return 0;
// }

// #include "test.h"

// int main()
// {
//   // 充当服务端
//   key_t key = CreateKey();
//   int shmgetId = shmget(key, 1024, IPC_CREAT | IPC_EXCL | 0666);
//   cout << "服务端 key   " << key << "   shmgetId   " << shmgetId << endl;
//   return 0;
// }

// int main()
// {

//   printf("hello printf"); // stdout 中写

//   const char *msg = "hello write";

//   write(1, msg, strlen(msg));
//   sleep(5);
//   return 0;
// }

// int main()
// {
//   umask(0);

//   close(1);
//   int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666); // 1
//   if (fd < 0)
//   {
//     printf("%s\n", strerror(errno));
//     exit(1);
//   }
//   printf("fd %d\n", fd);

//   close(fd);
//   return 0;
// }

/// @brief
/// @return
// int main()
// {
//   umask(0);
//   int fd1 = open("log.txt", O_WRONLY | O_CREAT, 0666); // 666 -- >110 110 110
//   int arr[] = {1, 2, 3, 4};
//   int sz = sizeof(arr);

//   write(fd1, (char *)arr, sz); // 注意  带 '\0' 是C语言的风格,文件可是不做要求的.
//   close(fd1);
//   int fd2 = open("log.txt", O_RDONLY, 0666);
//   int arr2[4] = {0};
//   read(fd2, (char *)arr2, sizeof(arr2));
//   for (int i = 0; i < 4; i++)
//   {
//     cout << arr2[i] << " ";
//   }
//   cout << endl;
//   return 0;
// }

// #define PRINT_A 0x01 // 0000 0001
// #define PRINT_B 0x02 // 0000 0010
// #define PRINT_C 0x04 // 0000 0100
// #define PRINT_D 0x08 // 0000 1000
// #define PRINT_DEL 0x00

// void Show(int flags)
// {
//   if (flags & PRINT_A)
//     printf("hello A\n");

//   if (flags & PRINT_B)
//     printf("hello B\n");
//   if (flags & PRINT_C)
//     printf("hello C\n");
//   if (flags & PRINT_D)
//     printf("hello D\n");
//   if (flags == PRINT_DEL)

//     printf("hello default\n");
// }

// int main()
// {
//   Show(PRINT_DEL);
//   printf("\n\n");

//   Show(PRINT_A);
//   printf("\n\n");

//   Show(PRINT_B | PRINT_C | PRINT_D);
//   return 0;
// }