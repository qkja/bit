#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;


int main()
{
    //open("log.txt",)
    return 0;
}


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
//         return 1;
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
