#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include <ctime>
#include <cassert>
#include <cstdlib>

#include <unistd.h>
#include <sys/wait.h>

using namespace std;

















//  兄弟进程如何通信   要知道 这里打开时 2个管道文件
//

// typedef void (*functor)(); // 函数指针
// vector<functor> functors;  // 方法集合
// unordered_map<uint32_t, string> info;
// //  pid  fd
// typedef std::pair<int32_t, int32_t> elem;

// // 定义子进程的个数
// int processNum = 5;

// void f1()
// {
//     cout << "这是一个处理日志的任务,执行进程的pid ["
//          << getpid() << "] 执行时间 [" << time(nullptr) << "]\n" << endl;
// }

// void f2()
// {
//     cout << "这是一个备份数据的任务,执行进程的pid ["
//          << getpid() << "] 执行时间 [" << time(nullptr) << "]\n" << endl;
// }

// void f3()
// {
//     cout << "这是一个处理网络链接的任务,执行进程的pid ["
//          << getpid() << "] 执行时间 [" << time(nullptr) << "]\n" << endl;
// }

// // 加载方法
// void LoadFunctor()
// {
//     // 加载
//     info.insert(make_pair(functors.size(), "处理日志"));
//     functors.push_back(f1);

//     info.insert(make_pair(functors.size(), "备份数据"));
//     functors.push_back(f2);

//     info.insert(make_pair(functors.size(), "处理网络"));
//     functors.push_back(f3);
// }

// void Work(int fd)
// {
//     cout << "进程pid [" << getpid() << "] 开始工作" << endl;
//     while (true)
//     {
//         uint32_t code = 0;
//         // 什么时候会读到 0
//         // 阻塞到这了
//         ssize_t s = read(fd, &code, sizeof(uint32_t));
//         if (s == 0)
//         {
//             break;
//         }
//         else if (s == sizeof(uint32_t))
//         {
//             if (code < functors.size())
//             {
//                 functors[code]();
//             }
//             else
//             {
//                 cout << "bug" << endl;
//             }
//         }
//         else
//         {
//             close(fd);
//             assert(false);
//         }
//     }

//     cout << "进程pid [" << getpid() << "] 结束工作" << endl;
// }

// void SendTask(const vector<elem> &assignMap)
// {
//     srand((long long)time(nullptr));
//     int cnt = 0;
//     while (cnt < 3)
//     {
//         cnt++;
//         // 选择一个进程
//         sleep(1);
//         int pick = rand() % assignMap.size();

//         // 选择一个任务
//         int task = rand() % functors.size();

//         // 把任务给一个指定的进程
//         // cout << "父进程指派  " << info[task] << "  给进程 pid  "
//         //      << assignMap[pick].first << "   编号是 " << pick << endl;
//         write(assignMap[pick].second, &task, sizeof(task));

//         // 打印提示信息
//         cout << "父进程指派  " << info[task] << "  给进程 pid  "
//              << assignMap[pick].first << "   进程编号是 " << pick << endl;
//         //fflush(stdout);
//          //sleep(1);
//         //sleep(10);
//     }

//     // 指派任务结束后 ,我们需要关闭 写端
//     for (int i = 0; i < processNum; i++)
//     {
//         close(assignMap[i].second);
//     }
    
// }

// int main()
// {

//     vector<elem> assignMap;
//     LoadFunctor();
//     for (size_t i = 0; i < processNum; i++)
//     {
//         int pipeFd[2] = {0};
//         pipe(pipeFd);

//         pid_t id = fork();
//         if (id == 0)
//         {
//             // 只有子进程会进入到了
//             close(pipeFd[1]);

//             Work(pipeFd[0]);

//             close(pipeFd[0]);
//             exit(0);
//         }
//         // 只有父进程
//         // 如何给子进程指派任务
//         // 需要保存 进程 和 对应的文件描述符
//         close(pipeFd[0]);
//         elem e(id, pipeFd[1]);
//         assignMap.push_back(e);
//     }

//     // 到这里一定 是父进程
//     SendTask(assignMap);

//     // 这一步肯定是指派任务结束了
//     for (int i = 0; i < processNum; i++)
//     {
//         if (waitpid(assignMap[i].first, nullptr, 0))
//         {
//             cout << "等待成功 pid" << assignMap[i].first
//                  << "ppid " << getpid()
//                  << "  编号   " << i << endl;
//             //close(assignMap[i].second);
//         }
//     }
//     return 0;
// }

// 测试多进程是不是打开不同的描述符
// int main()
// {

//     for (size_t i = 0; i < processNum; i++)
//     {
//         int pipeFd[2] = {0};
//         pipe(pipeFd);

//         pid_t id = fork();
//         if(id == 0)
//         {
//             cout << pipeFd[0] <<endl;
//             cout << pipeFd[1] <<endl;
//             break;
//         }
//     }

//     return 0;
// }

// 控制一个进程
// int main()
// {
//     // 0 先来加载方法
//     srand((long long)time(nullptr));
//     LoadFunctor();
//     int pipeFd[2] = {0};
//     // successful completion, 0
//     // errno -1
//     if (pipe(pipeFd) != 0)
//     {
//         cerr << "pipe errno" << endl;
//         return 1;
//     }

//     // 创建子进程
//     pid_t id = fork();
//     if (id == 0)
//     {
//         // child
//         // 关闭写
//         close(pipeFd[1]);
//         while (true)
//         {
//             // 读取父进程的给的任务
//             // 从 fd 为 fildes 读取 nbyte字节 到 buf指向的空间中
//             // 返回值 读取的字节数
//             // ssize_t read(int fildes, void *buf, size_t nbyte);
//             uint32_t operatorType = 0;
//             ssize_t s = read(pipeFd[0], &operatorType, sizeof(uint32_t));
//             if (s == 0)
//             {
//                 // 这里一定是父进程给关了
//                 cout << "父进程结束了,我也要走了" << endl;
//                 break;
//             }

//             assert(s == sizeof(uint32_t));

//             (void)s; // release 版本可能汇报警告 只定义 不使用

//             if (operatorType < functors.size())
//             {
//                 functors[operatorType]();
//             }
//             else
//             {
//                 cerr << "bug ? operatorType = " << operatorType << endl;
//                 exit(2);
//             }
//             // 肯定读取了 相关字节
//             // if(s == sizeof(uint32_t))
//             // {
//             //     if(operatorType < functors.size())
//             //     {
//             //         functors[operatorType]();
//             //     }
//             //     else
//             //     {
//             //         cerr << "bug ? operatorType = "  << operatorType<< endl;
//             //         exit(2);
//             //     }
//             // }
//             // else
//             // {

//             // }

//             //
//         }
//         close(pipeFd[0]);

//         exit(0);
//     }
//     else if (id > 0)
//     {
//         // parent
//         // 关闭读
//         close(pipeFd[0]);
//         // 这里开始让子进程做任务
//         int cnt = 0;

//         while (cnt < 5)
//         {
//             uint32_t sendTask = 0;
//             printf("请输入你要执行的命令:");
//             fflush(stdout);
//             scanf("%d",&sendTask);
//             //sendTask = rand() % functors.size();
//             sendTask =sendTask % functors.size();
//             cout << "父进程指派任务完成,任务是   " << info[sendTask]
//                  << "   任务编号" << cnt << endl;
//             // ssize_t write(int fildes, const void *buf, size_t nbyte);
//             write(pipeFd[1], &sendTask, sizeof(uint32_t));
//             sleep(2);
//             cnt++;
//         }
//         // 做完了
//         close(pipeFd[1]);
//         // 这个等待子进程
//         // pid_t waitpid(pid_t pid, int *stat_loc, int options);
//         pid_t ret = waitpid(id, nullptr, 0);
//         if (ret > 0)
//         {
//             // 等待成功
//             cout << "等待子进程成功" << endl;
//         }
//         else
//         {
//             // do Nothing
//         }
//     }
//     else
//     {
//         // errno
//     }
//     return 0;
// }