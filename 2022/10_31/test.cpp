#include <vector>
#include <ctime>
#include <iostream>
#include <cassert>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <sys/wait.h>

using namespace std;

typedef void (*functor)(); // 函数指针
vector<functor> functors;  // 方法集合
unordered_map<uint32_t, string> info;

void f1()
{
    cout << "这是一个处理日志的任务,执行进程的pid ["
         << getpid() << "] 执行时间 [" << time(nullptr) << "]" << endl;
}

void f2()
{
    cout << "这是一个备份数据的任务,执行进程的pid ["
         << getpid() << "] 执行时间 [" << time(nullptr) << "]" << endl;
}

void f3()
{
    cout << "这是一个处理网络链接的任务,执行进程的pid ["
         << getpid() << "] 执行时间 [" << time(nullptr) << "]" << endl;
}

// 加载方法
void LoadFunctor()
{
    // 加载
    info.insert(make_pair(functors.size(), "处理日志"));
    functors.push_back(f1);

    info.insert(make_pair(functors.size(), "备份数据"));
    functors.push_back(f2);

    info.insert(make_pair(functors.size(), "处理网络"));
    functors.push_back(f3);
}

int main()
{
    // 0 先来加载方法
    srand((long long)time(nullptr));
    LoadFunctor();
    int pipeFd[2] = {0};
    // successful completion, 0
    // errno -1
    if (pipe(pipeFd) != 0)
    {
        cerr << "pipe errno" << endl;
        return 1;
    }

    // 创建子进程
    pid_t id = fork();
    if (id == 0)
    {
        // child
        // 关闭写
        close(pipeFd[1]);
        while (true)
        {
            // 读取父进程的给的任务
            // 从 fd 为 fildes 读取 nbyte字节 到 buf指向的空间中
            // 返回值 读取的字节数
            // ssize_t read(int fildes, void *buf, size_t nbyte);
            uint32_t operatorType = 0;
            ssize_t s = read(pipeFd[0], &operatorType, sizeof(uint32_t));
            if (s == 0)
            {
                // 这里一定是父进程给关了
                cout << "父进程结束了,我也要走了" << endl;
                break;
            }

            assert(s == sizeof(uint32_t));

            (void)s; // release 版本可能汇报警告 只定义 不使用

            if (operatorType < functors.size())
            {
                functors[operatorType]();
            }
            else
            {
                cerr << "bug ? operatorType = " << operatorType << endl;
                exit(2);
            }
            // 肯定读取了 相关字节
            // if(s == sizeof(uint32_t))
            // {
            //     if(operatorType < functors.size())
            //     {
            //         functors[operatorType]();
            //     }
            //     else
            //     {
            //         cerr << "bug ? operatorType = "  << operatorType<< endl;
            //         exit(2);
            //     }
            // }
            // else
            // {

            // }

            //
        }
        close(pipeFd[0]);

        exit(0);
    }
    else if (id > 0)
    {
        // parent
        // 关闭读
        close(pipeFd[0]);
        // 这里开始让子进程做任务
        int cnt = 0;

        while (cnt < 5)
        {
            uint32_t sendTask = 0;
            sendTask = rand() % functors.size();
            cout << "父进程指派任务完成,任务是   " << info[sendTask]
                 << "   任务编号" << cnt << endl;
            // ssize_t write(int fildes, const void *buf, size_t nbyte);
            write(pipeFd[1], &sendTask, sizeof(uint32_t));
            sleep(2);
            cnt++;
        }
        // 做完了
        close(pipeFd[1]);
        // 这个等待子进程
        // pid_t waitpid(pid_t pid, int *stat_loc, int options);
        pid_t ret = waitpid(id, nullptr, 0);
        if (ret > 0)
        {
            // 等待成功
            cout << "等待子进程成功" << endl;
        }
        else
        {
            // do Nothing
        }
    }
    else
    {
        // errno
    }
    return 0;
}