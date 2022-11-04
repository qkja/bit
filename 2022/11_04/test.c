/**
 * Author       : Qkj
 * Description  : 基础IO
 * Date         : 2022-11-04 18:17:05
 * LastEditTime : 2022-11-04 20:33:59
 */
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// 用的不安稳


/*
open 函数   
 参数1 文件名(包含路径)
 参数2 文件传递的选项
 参数3 文件权限 和 umask 有关



 返回值   很特殊 -1 表示错误   
*/

//    int open(const char *pathname, int flags);
//    int open(const char *pathname, int flags, mode_t mode);

// w我们需要看 5 个宏

// O_APPEND 
// O_CREAT 
// O_WRONLY
// O_RDONLY

// 一般 我们使用  位图 的方式    int 类型有32个比特位  
// 我们写一个代码实现一下

int main()
{
    int fd = open("log.txt", O_CREAT | O_WRONLY);
    if(fd < 0)
    {
        perror("open");
        return 1;
    }

    return 0;
}






// void f(int a)
// {
//     printf("f(int a)\n");
// }

// void f(int a, int b)
// {
//     printf("f(int a, int b)\n");
// }

// int main()
// {
//     // C语言在gcc编译器下应该也不支持重载 或许可以看看GNU计划
//       // 但是
//     f(1);
//     f(1, 2);
//     return 0;
// }