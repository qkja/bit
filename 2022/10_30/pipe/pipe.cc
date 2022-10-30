#include <iostream>
#include <cstring>
#include <string>
#include <cassert>
#include <unistd.h>
#include <sys/wait.h>
#include <ctime>
using namespace std;

int main()
{

    //srand((long long)time(nullptr));
    int pipefd[2] = {0};
    // 创建管道
    if(pipe(pipefd) != 0)
    {
        cerr << "pipe error" << endl;
        return 1;
    }

    // 到这里 我们开始创建子进从程
    pid_t id = fork();

    if(id == 0)
    {
        // child
        // 子进程经行读取 关闭写
        close(pipefd[1]);

        const int NUM = 1024;
        char buffer[NUM] = {0};
        // 开始读
        while(true)
        {
            // 清空

            cout << "时间戳 " << (uint64_t)time(nullptr) << endl;
            //cout << rand() << endl;
            memset(buffer, '\0', sizeof(buffer));
            //ssize_t read(int fd, void *buf, size_t count);
            // 返回值  读取的字节数
            ssize_t s = read(pipefd[0], buffer, sizeof(buffer)-1);
            if(s > 0)
            {
                //读取成功
                buffer[s] = '\0';  // 注意细节
                cout << "子进程收到消息: " << buffer << endl;
            }
            else if(s == 0)
            {
                // 只有当写段关闭   这里读完所有的   就会返回0
                // 子进程为何会知道 写段关了   这里就是 引用计数
                cout << "父进程退出了, 我也退出" << endl;
                break;
            }
            else
            {
                // doNothing
            }
        }
        close(pipefd[0]);
        exit(0);
    }
    else if(id > 0)
    {
        // parent
        // 父进程进行写入 关掉读
        close(pipefd[0]);

        //const char* msg = "你好子进程,我是父进程";
        string msg = "你好子进程,我是父进程";
        int cnt = 0;
        while(cnt < 5)
        {
            //ssize_t write(int fd, const void *buf, size_t count);
            //abcd\0  这里\0 是C语言类型的  不要 + 1
            //write(pipefd[1], msg, strlen(msg));
            write(pipefd[1], msg.c_str(), msg.size());
            sleep(2);
            cnt++;
        }

        // 关闭  
        close(pipefd[1]);
        cout << "父进程写完了" << endl;
    }
    else
    {
        cerr << "fork error" << endl;
        return 2;
    }

    // 到这里一定时父进程
    //pid_t waitpid(pid_t pid, int *stat_loc, int options);
    // 这里是 阻塞等待
    pid_t ret = waitpid(id, nullptr, 0);
    if(ret > 0)
    {
        cout << "等待子进程成功" << endl;
    }
    else 
    {
        cerr << "等待失败" << endl;
    }
    //[0] 读
    //[1] 写
    return 0;
}


// 为何是单项的
// int main()
// {
//     int pipeArr[2] = {0};
//     int pipeArr1[2] = {0};
//     if(pipe(pipeArr) != 0)
//     {
//         cerr << "pipe errno" << endl;
//     }

//     if(pipe(pipeArr1) != 0)
//     {
//         cerr << "pipe errno" << endl;
//     }
//     cout << "hello" << endl;
//     // 里面保存的是  fd
//     cout << pipeArr[0] << endl;
//     cout << pipeArr[1] << endl;
//     cout << "hello" << endl;

//     cout << pipeArr1[0] << endl;
//     cout << pipeArr1[1] << endl;

//     return 0;
// }


// #include <iostream>
// #include <cstdio>
// #include <unistd.h>
// #include <cstdlib>

// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>

// using namespace std;


// int main()
// {
//     //open("log.txt",)
//     return 0;
// }


// 管道也是有大小的  内部没有数据  读端就必须阻塞等待  
// 如果数据被写满了  write就必须阻塞等待
// 后面的多线程的 互斥  同步
// 如何让父进程控制一批进程
// 
// int main()
// {
//     int pipefd[2] = {0};
//     if(pipe(pipefd) != 0)
//     {
//         cout << "pipe error" << endl;
//         return 1;~
//     }

//     // 这里开始创建进程
//     pid_t id = fork();
//     if(id == 0)
//     {
//         //child

//         // 这个做往之后直接退出
//         exit(0);
//     }    
//     else if(id > 0) 
//     {
//         // parent
//     }
//     else
//     {
//     }
//     //cout << "hello vscode" << endl;
//     return 0;
// }
