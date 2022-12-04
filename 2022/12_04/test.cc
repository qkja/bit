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

// int main()
// {
//   umask(0);
//   int fd = open("log.txt",  O_WRONLY | O_CREAT | O_TRUNC, 0666);
//   int val = 0x11223344;
//   //
//   char * msg = "abcd";
//   int len = strlen(msg);
//   //write(fd, msg, len);
//   write(fd,&val, 1);
//   val = 'D';
//   std::cout << val<< std::endl;
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

#define PRINT_A 0x01 // 0000 0001
#define PRINT_B 0x02 // 0000 0010
#define PRINT_C 0x04 // 0000 0100
#define PRINT_D 0x08 // 0000 1000
#define PRINT_DEL 0x00
void Show(int flags)
{
  if (flags & PRINT_A)
    printf("hello A\n");
  if (flags & PRINT_B)
    printf("hello B\n");
  if (flags & PRINT_C)
    printf("hello C\n");
  if (flags & PRINT_D)
    printf("hello D\n");
  if (flags == PRINT_DEL)

    printf("hello default\n");
}

int main()
{
  Show(PRINT_DEL);
  printf("\n\n");

  Show(PRINT_A);
  printf("\n\n");

  Show(PRINT_B | PRINT_C | PRINT_D);
  return 0;
}
