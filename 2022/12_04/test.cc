/**
 * User: Qkj
 * Description:
 * Date: 2022-12-03
 * Time: 23:48
 */
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <string>

int main()
{
    umask(0);

    close(1);
    int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0)
    {
        printf("%s\n", strerror(errno));
        exit(1);
    }
    printf("fd %d\n", fd);

    close(fd);
    return 0;
}

// void read(struct file *filep, int fd....)
// {
//   // 逻辑代码
// }

// void write(struct file *filep, int fd....)
// {
//   // 逻辑代码
// }
// struct file
// {
//   // 对象属性

//   //函数指针   这个是类型
//   void (*read)(struct file *filep, int fd....);
//   void (*write)(struct file *filep, int fd....);
// }

// struct file
// {

//   //文件 属性 + 内容

//   struct file *prev;
//   struct file *next;
// };

// int main()
// {
//   umask(0);

//   const char *msg = "123456\n";

//   write(1, msg, strlen(msg));
//   return 0;
// }
// int main()
// {
//   umask(0);
//   char buffer[128];
//   // 从 fd = 0的是文件中去读,读到内容放在 buffer中
//   ssize_t s = read(0, buffer, sizeof(buffer) - 1);

//   if (s > 0)
//   {
//     buffer[s] = '\0';
//     printf("输出 %s", buffer);
//   }
//   return 0;
// }
// int main()
// {
//   umask(0);

//   printf("stdin   : %d\n", stdin->_fileno);
//   printf("stdout  : %d\n", stdout->_fileno);
//   printf("stderr  : %d\n", stderr->_fileno);

//   return 0;
// }

// int main()
// {
//   umask(0);
//   FILE* pf1 = fopen("log1.txt","w");
//   FILE* pf2 = fopen("log2.txt","w");
//   FILE* pf3 = fopen("log3.txt","w");

//   printf("pf1 : %d\n", pf1->_fileno);
//   printf("pf2 : %d\n", pf2->_fileno);
//   printf("pf3 : %d\n", pf3->_fileno);

//   return 0;
// }

// int main()
// {
//   umask(0);
//   int fd = open("log.txt", O_RDONLY, 0666);

//   char buffer[128];
//   ssize_t s = read(fd, buffer, sizeof(buffer) - 1);
//   if (s > 0)
//   {
//     buffer[s] = '\0'; // 这个注意下标
//     printf("%d %s", s, buffer);
//   }
//   return 0;
// }

// int main()
// {
//   umask(0);
//   int fd = open("file.txt", O_RDONLY, 0666);

//   if (fd < 0)
//   {
//     printf("%s\n", strerror(errno));
//     exit(1);
//   }

//   printf("fd %d\n", fd);
//   char buffer[128];
//   ssize_t s = read(fd, buffer, sizeof(buffer) - 1);
//   if (s > 0)
//   {
//     buffer[s] = '\0'; // 这个注意下标
//     printf("%s\n", buffer);
//   }
//   return 0;
// }

// int main()
// {
//   umask(0);
//   int fd = open("log.txt",  O_WRONLY | O_CREAT | O_TRUNC, 0666);
//   int val = 0x41424344;
//   char * msg = "abcd";
//   int len = strlen(msg);
//   write(fd,&val, 4);
//   close(fd);

//   return 0;
// }

// int main()
// {
//   umask(0);
//   int fd = open("log.txt", O_WRONLY | O_CREAT, 0666);

//   const char *str = "1234567";
//   int len = strlen(str);

//   write(fd, str, len);

//   return 0;
// }

// int main()
// {
//   umask(0);
//   int fd = open("log.txt",  O_WRONLY | O_CREAT | O_TRUNC, 0666);
//   int val = 0x41424344;
//   //
//   char * msg = "abcd";
//   int len = strlen(msg);
//   //write(fd, msg, len);
//   write(fd,&val, 4);
//   // val = 'D';
//   // std::cout << val<< std::endl;
//   close(fd);

//   return 0;
// }

// int main()
// {
//   FILE* fp = fopen("test.cc", "r");
//   int ret = fp->_fileno;
//   std::cout << ret<<std::endl;
//   return 0;
// }

// int main()
// {
//   umask(0);
//   int fd = open("log.txt", O_WRONLY | O_CREAT, 0666);
//   close(fd);
//   close(fd);

//   return 0;
// }

// int main()
// {
//   umask(0);
//   int fd = open("log.txt", O_WRONLY | O_CREAT, 0666);

//   const char *str = "abcdef";
//   int len = strlen(str);

//   write(fd, str, len); // 注意  带 \0 是C语言的风格 ,文件可是不做要求的

//   return 0;
// }

// int main()
// {
//   umask(0);
//   int fd = open("log.txt", O_WRONLY, 0666);
//   if (fd < 0)
//   {
//     std::cout << "fd: " << fd << "  " << strerror(errno) << std::endl;
//     return 1;
//   }
//   return 0;
// }

// int main()
// {
//   umask(0);
//   //int fd = open("log.txt", O_RDONLY, 0666);
//   int fd = open("log.txt", O_CREAT|O_TRUNC, 0666);
//   if (fd < 0)
//   {
//     std::cout << "fd: " << fd << "  " << strerror(errno) << std::endl;
//     return 1;
//   }
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
