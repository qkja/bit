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
int main()
{
  key_t key = ftok(PATH_NAME, PROJ_ID);

  int shmid = shmget(key, MEM_SIZE, IPC_CREAT);
  char *str = (char *)shmat(shmid, nullptr, 0);
  const char *p = "i am process A";
  strcpy(str, p);
  shmdt(str);
  return 0;
}
// #include <iostream>
// #include <unistd.h>
// #include <error.h>
// #include <cstring>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>

// #include <stdlib.h>
// using namespace std;

// #define FILE_PATH ".fifo"
// int main()
// {
//   int fd =  open(FILE_PATH, O_WRONLY);
//   string str ="i am process A";
//   write(fd, str.c_str(), str.size());
//   return 0;
// }

// #include "test.h"

// int main()
// {
//   // 充当客户端
//   key_t key = CreateKey();
//   int shmgetId = shmget(key, 1024, IPC_CREAT | IPC_EXCL | 0666);
//   cout << "客户端 key   " << key << "   shmgetId   " << shmgetId << endl;
//   return 0;
// }

// #define PATH_NAME "/home/bit/104/2022/12_12"
// #define PROJ_ID 0x14
// #define MEM_SIZE 4096

// #define FIFO_FILE ".fifo"
// std::ostream &Log()
// {
//   std::cout << "Fot Debug |"
//             << " timestamp: " << (uint64_t)time(nullptr) << " | ";
//   return std::cout;
// }
// key_t CreateKey()
// {
//   key_t key = ftok(PATH_NAME, PROJ_ID);
//   if (key < 0)
//   {
//     std::cerr << "ftok: " << strerror(errno) << std::endl;
//     exit(1);
//   }
//   return key;
// }
// int flags = IPC_CREAT | IPC_EXCL;
// int main()
// {
//   umask(8);
//   key_t key = CreateKey();
//   Log() << "key: " << key << std::endl;
//   int shmid = shmget(key, MEM_SIZE, flags | 0666);
//   if (shmid < 0)
//   {
//     Log() << "shmget fali  " << strerror(errno) << std::endl;
//     return 1;
//   }

//   Log() << "shmget success  shmid " << shmid << std::endl;

//   // 这里使用共享内存
//   // 挂接
//   Log() << "shmat begin " << std::endl;
//   char *str = (char *)shmat(shmid, nullptr, 0);
//   sleep(5);
//   Log() << "shmctl begin " << std::endl;

//   shmctl(shmid, IPC_RMID, nullptr);
//   Log() << "shmctl success  shmid " << shmid << std::endl;
//   sleep(5);

//   return 0;
// }

// #include <iostream>
// #include <unistd.h>
// #include <stdio.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <iostream>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <assert.h>
// #include <string.h>
// #include <vector>
// #include <unordered_map>
// using namespace std;

// int main()
// {
//   int pipeFd[2] = {0};
//   pipe(pipeFd);
//   int ret = 0;
//   char ch = ' ';
//   while (true)
//   {
//     write(pipeFd[1], &ch, 1);
//     ret++;
//     cout << "已经写入 " << ret << "个字节" << endl;
//   }

//   return 0;
// }

// int main()
// {
//   int pipeFd[2] = {0};
//   pipe(pipeFd);
//   int ret = 0;
//   //close(pipeFd[0]);
//   char* ch = "a";
//   while (true)
//   {
//     write(pipeFd[1], ch, strlen(ch));
//     ret++;
//     cout << "已经写入 " << ret << "个字节" << endl;
//   }

//   return 0;
// }

// typedef void (*functor)();

// vector<functor> functors; // 方法集合
// // for debug
// unordered_map<uint32_t, string> info;
// // int32_t: 进程pid, int32_t: 该进程对应的管道写端fd
// typedef std::pair<int32_t, int32_t> elem;
// int processNum = 5;

// void f1()
// {
//   cout << "这是一个处理日志的任务, 执行的进程 ID [" << getpid() << "]"
//        << "执行时间是[" << time(nullptr) << "]\n"
//        << endl;
// }
// void f2()
// {
//   cout << "这是一个备份数据任务, 执行的进程 ID [" << getpid() << "]"
//        << "执行时间是[" << time(nullptr) << "]\n"
//        << endl;
// }
// void f3()
// {
//   cout << "这是一个处理网络连接的任务, 执行的进程 ID [" << getpid() << "]"
//        << "执行时间是[" << time(nullptr) << "]\n"
//        << endl;
// }

// void loadFunctor()
// {
//   info.insert({functors.size(), "处理日志的任务"});
//   functors.push_back(f1);

//   info.insert({functors.size(), "备份数据任务"});
//   functors.push_back(f2);

//   info.insert({functors.size(), "处理网络连接的任务"});
//   functors.push_back(f3);
// }

// void work(int blockFd)
// {
//   cout << "进程[" << getpid() << "]"
//        << " 开始工作" << endl;
//   // 子进程核心工作的代码
//   while (true)
//   {
//     // a.阻塞等待  b. 获取任务信息
//     uint32_t operatorCode = 0;
//     ssize_t s = read(blockFd, &operatorCode, sizeof(uint32_t));
//     if (s == 0)
//       break;
//     assert(s == sizeof(uint32_t));
//     (void)s;

//     // c. 处理任务
//     if (operatorCode < functors.size())
//       functors[operatorCode]();
//   }
//   cout << "进程[" << getpid() << "]"
//        << " 结束工作" << endl;
// }

// // [子进程的pid, 子进程的管道fd]
// void blanceSendTask(const vector<elem> &processFds)
// {
//   int ret = 0;
//   srand((long long)time(nullptr));
//   while (ret < 7)
//   {
//     ret++;
//     sleep(1);
//     // 选择一个进程, 选择进程是随机的，没有压着一个进程给任务
//     // 较为均匀的将任务给所有的子进程 --- 负载均衡
//     uint32_t pick = rand() % processFds.size();

//     // 选择一个任务
//     uint32_t task = rand() % functors.size();

//     // 把任务给一个指定的进程
//     write(processFds[pick].second, &task, sizeof(task));

//     // 打印对应的提示信息
//     cout << "父进程指派任务->" << info[task] << "给进程: " << processFds[pick].first << " 编号: " << pick << endl;
//   }
// }

// int main()
// {
//   loadFunctor();
//   vector<elem> assignMap;
//   // 创建processNum个进程
//   for (int i = 0; i < processNum; i++)
//   {
//     // 定义保存管道fd的对象
//     int pipefd[2] = {0};
//     // 创建管道
//     pipe(pipefd);
//     // 创建子进程
//     pid_t id = fork();
//     if (id == 0)
//     {
//       // 子进程读取, r -> pipefd[0]
//       close(pipefd[1]);
//       // 子进程执行
//       work(pipefd[0]);
//       close(pipefd[0]);
//       exit(0);
//     }
//     // 父进程做的事情, pipefd[1]
//     close(pipefd[0]);
//     elem e(id, pipefd[1]);
//     assignMap.push_back(e);
//   }
//   cout << "create all process success!" << std::endl;
//   // 父进程, 派发任务
//   blanceSendTask(assignMap);

//   // 回收资源
//   for (int i = 0; i < processNum; i++)
//   {
//     if (waitpid(assignMap[i].first, nullptr, 0) > 0)
//       cout << "wait for: pid=" << assignMap[i].first << " wait success!"
//            << "number: " << i << "\n";
//     close(assignMap[i].second);
//   }
// }

// typedef void (*functor)(); // 函数指针

// vector<functor> functors;             // 方法集合
// unordered_map<uint32_t, string> info; // 任务描述
// void f1()
// {
//   cout << "这是一个处理日志的任务, 执行的进程 ID [" << getpid() << "]"
//        << "执行时间是[" << time(nullptr) << "]\n"
//        << endl;
//        sleep(10);
// }
// void f2()
// {
//   cout << "这是一个备份数据任务, 执行的进程 ID [" << getpid() << "]"
//        << "执行时间是[" << time(nullptr) << "]\n"
//        << endl;
// }
// void f3()
// {
//   cout << "这是一个处理网络连接的任务, 执行的进程 ID [" << getpid() << "]"
//        << "执行时间是[" << time(nullptr) << "]\n"
//        << endl;
// }

// void loadFunctor()
// {
//   info.insert({functors.size(), "处理日志的任务"});
//   functors.push_back(f1);

//   info.insert({functors.size(), "备份数据任务"});
//   functors.push_back(f2);

//   info.insert({functors.size(), "处理网络连接的任务"});
//   functors.push_back(f3);
// }
// void work(int blockFd)
// {
//   cout << "进程[" << getpid() << "]"
//        << " 开始工作" << endl;
//   // 子进程核心工作的代码
//   while (true)
//   {
//     // a.阻塞等待  b. 获取任务信息
//     uint32_t operatorCode = 0;
//     ssize_t s = read(blockFd, &operatorCode, sizeof(uint32_t));
//     if (s == 0)
//       break;
//     assert(s == sizeof(uint32_t));
//     (void)s;

//     // c. 处理任务
//     if (operatorCode < functors.size())
//       functors[operatorCode]();
//   }
//   cout << "进程[" << getpid() << "]"
//        << " 结束工作" << endl;
// }

// int main()
// {
//   // 0. 加载任务列表
//   loadFunctor();

//   // 1. 创建管道
//   int pipefd[2] = {0};
//   if (pipe(pipefd) != 0)
//   {
//     cerr << "pipe error" << endl;
//     return 1;
//   }

//   // 2. 创建子进程
//   pid_t id = fork();
//   if (id < 0)
//   {
//     cerr << " fork error " << endl;
//     return 2;
//   }
//   else if (id == 0)
//   {
//     // 3. 关闭不需要的文件fd
//     // child,read
//     close(pipefd[1]);
//     // 4. 业务处理
//     while (true)
//     {
//       uint32_t operatorType = 0;
//       // 如果有数据，就读取，如果没有数据，就阻塞等待, 等待任务的到来
//       // 我们规定了 写端是写入4个字节,那么读应该也是4个字节,这是一种规定
//       ssize_t s = read(pipefd[0], &operatorType, sizeof(uint32_t));
//       if (s == 0)
//       {
//         cout << "我要退出啦,我是给人打工的,老板都走了...." << endl;
//         break;
//       }
//       assert(s == sizeof(uint32_t));

//       (void)s;

//       if (operatorType < functors.size())
//       {
//         // 处理任务
//         functors[operatorType]();
//       }
//       else
//       {
//         cerr << "bug? operatorType = " << operatorType << std::endl;
//       }
//     }
//     close(pipefd[0]);
//     exit(0);
//   }
//   else
//   {
//     srand((long long)time(nullptr));
//     // parent,write - 操作
//     // 3. 关闭不需要的文件fd
//     close(pipefd[0]);
//     // 4. 指派任务
//     int num = functors.size();
//     int cnt = 10;
//     while (cnt--)
//     {
//       // 5. 形成任务码
//       uint32_t commandCode = rand() % num;
//       std::cout << "父进程指派任务完成，任务是: " << info[commandCode] << " 任务的编号是: " << cnt << std::endl;
//       // 向指定的进程下达执行任务的操作
//       write(pipefd[1], &commandCode, sizeof(uint32_t));
//       sleep(1);
//     }

//     // 注意一定要在这关闭写端,否则我们子进程一定会阻塞到哪里,那么父进程根本无法拿到子进程的资源
//     close(pipefd[1]);
//     pid_t res = waitpid(id, nullptr, 0);
//     if (res)
//       cout << "wait success" << endl;
//   }
//   return 0;
// }

// int main()
// {
//   int pipefd[2] = {0};
//   if (pipe(pipefd) != 0)
//   {
//     cerr << "pipe open fail" << errno << endl;
//   }
//   // 创建子进程
//   pid_t id = fork();
//   if (id == 0)
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

// int func()
// {
//   int fd = open("./tmp.txt", O_RDWR | O_CREAT, 0664);
//   if (fd < 0)
//   {
//     return -1;
//   }
//   dup2(fd, 1);
//   printf("hello bit");
//   return 0;
// }
// int main()
// {
//   func();
//       // umask(0);

//       // close(1);
//       // int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666); // 1
//       // if (fd < 0)
//       // {
//       //   printf("%s\n", strerror(errno));
//       //   exit(1);
//       // }
//       // printf("fd %d\n", fd);

//       // close(fd);
//       return 0;
// }

// int main()
// {
//   umask(0);
//   pid_t id = fork();
//   if (id == 0)
//   {
//     // 子进程
//     int fd = open("log.txt", O_RDONLY | O_TRUNC, 666);
//     cout << "子进程 " << fd << endl;
//     sleep(5);
//     exit(10);
//   }
//   sleep(1);
//   // 在这里等待子进程
//   int fd = open("log.txt", O_RDONLY | O_TRUNC, 666);

//   pid_t ret = waitpid(id, nullptr, 0);

//   if (ret > 0)
//   {
//     cout << "父进程 " << fd << endl;
//   }

//   return 0;
// }

// int main()
// {
//   umask(0);
//   pid_t id = fork();
//   if (id == 0)
//   {
//     // 子进程
//     int fd = open("log.txt", O_RDONLY | O_TRUNC, 666);
//     cout << fd << endl;
//     sleep(2);
//     exit(10);
//   }
//   sleep(1);

//   int status = 0;
//   // 在这里等待子进程
//   int fd = open("log.txt", O_RDONLY | O_TRUNC, 666);
//   cout << "父进程 "<<fd << endl;

//   pid_t ret = waitpid(id, &status, 0);

//   if (ret > 0)
//   {
//     // 此时有可能等待成功
//     if (WIFEXITED(status))
//     {
//       // 此时是正常退出的
//       cout << WEXITSTATUS(status) << endl;
//     }
//   }
//   else
//   {
//     // 对于阻塞,我们这里认为直接死亡
//     assert(nullptr);
//   }
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