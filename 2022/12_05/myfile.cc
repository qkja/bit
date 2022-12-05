/**
 * User: Qkj
 * Description:
 * Date: 2022-12-05
 * Time: 16:40
 */
#include <string.h>
#include <iostream>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  
}

// int main()
// {

//   const char *str1 = "hello printf\n";
//   const char *str2 = "hello fprintf\n";
//   const char *str3 = "hello fputs\n";
//   const char *str4 = "hello write\n";

//   printf("%s", str1);
//   fprintf(stdout, "%s", str2);
//   fputs(str3, stdout);

//   write(1, str4, strlen(str4));

//   fork();
//   return 0;
// }

// int main()
// {

//   printf("hello printf"); // stdout 中写

//   const char *msg = "hello write";

//   write(1, msg, strlen(msg));
//   close(1);

//   sleep(5);

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

//   printf("hello printf\n");
//   const char *msg = "hello write\n";
//   write(1, msg, strlen(msg));
//   sleep(5);
//   return 0;
// }

// int main()
// {
//   int fd = open("log.txt", O_RDONLY | O_CREAT, 0666);
//   if (fd < 0)
//   {
//     printf("%s\n", strerror(errno));
//     exit(1);
//   }
//   int ret = dup2(fd, 0);
//   if (ret >= 0)
//   {
//     close(fd);
//   }

//   char buffer[64];

//   while (fgets(buffer, sizeof(buffer), stdin) != NULL)
//   {
//     printf("%s\n", buffer);
//   }
//   return 0;
// }

// int main()
// {
//   int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
//   if (fd < 0)
//   {
//     printf("%s\n", strerror(errno));
//     exit(1);
//   }
//   int ret = dup2(fd, 1);
//   if (ret >= 0)
//   {
//     close(fd);
//   }

//   printf("ret %d\n", ret);
//   printf("打开文件成功 fd %d\n", fd);
//   return 0;
// }

// int main()
// {
//   int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
//   if (fd < 0)
//   {
//     printf("%s\n", strerror(errno));
//     exit(1);
//   }
//   int ret = dup2(fd, 1);
//   if (ret >= 0)
//   {
//     close(fd);
//   }
//   printf("ret %d\n", ret);
//   printf("打开文件成功 fd %d\n", fd);
//   return 0;
// }

// int main()
// {

//   int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
//   if (fd < 0)
//   {
//     printf("%s\n", strerror(errno));
//     exit(1);
//   }

//   dup2(fd, 1); // 这么传

//   printf("打开文件成功 fd %d\n", fd);
//   return 0;
// }

// int main()
// {
//   close(1);
//   int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
//   if (fd < 0)
//   {
//     printf("%s\n", strerror(errno));
//     exit(1);
//   }

//   fprintf(stdout, "%s %d\n", "打开文件成功", fd);

//   fflush(stdout);
//   close(fd);

//   return 0;
// }

// int main()
// {
//   close(1);
//   int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
//   if (fd < 0)
//   {
//     printf("%s\n", strerror(errno));
//     exit(1);
//   }

//   fprintf(stdout, "%s %d\n", "打开文件成功", fd);

//   close(fd);

// int main()
// {
//   int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
//   if (fd < 0)
//   {
//     printf("%s\n", strerror(errno));
//     exit(1);
//   }

//   fprintf(stdout, "%s %d\n", "打开文件成功", fd);

//   close(fd);
//   return 0;
// }

// int main()
// {
//   umask(0);

//   close(1);
//   int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
//   if (fd < 0)
//   {
//     printf("%s\n", strerror(errno));
//     exit(1);
//   }

//   printf("fd %d\n", fd);
//   fflush(stdout);
//   close(fd);
//   return 0;
// }

// int main()
// {
//   umask(0);

//   close(1);
//   int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
//   if (fd < 0)
//   {
//     printf("%s\n", strerror(errno));
//     exit(1);
//   }
//   char* p = "123";
//   write(stdout->_fileno, p,3);
//  // printf("fd %d\n", fd);
//  // fflush(stdout);
//   close(fd);
//   return 0;
// }
