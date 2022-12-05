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
#include <assert.h>
#include <fcntl.h>
#define NUM 1024
#define NONE_FLUSH 0x0 // 无缓冲
#define LINE_FLUSH 0x1 // 行缓冲
#define FULL_FLUSH 0x2 // 全缓冲

typedef struct MyFILE
{
  int _fd;
  char _buffer[NUM];
  int _flags; // 刷新策略
  int _end;   // buffer的结尾
} MyFILE;

void my_fflush(MyFILE *pf)
{
  assert(pf);
  if (pf->_end > 0)
  {
    write(pf->_fd, pf->_buffer, pf->_end);
    pf->_end = 0;
    syncfs(pf->_fd);
  }
}

MyFILE *my_fopen(char *filename, char *mode)
{
  assert(filename);
  assert(mode);
  int flags = O_RDONLY;
  if (strcmp(mode, "r") == 0)
  {
  }
  else if (strcmp(mode, "r+") == 0)
  {
  }
  else if (strcmp(mode, "w") == 0)
  {
    flags = O_WRONLY | O_CREAT | O_TRUNC;
  }
  else if (strcmp(mode, "w+") == 0)
  {
  }
  else if (strcmp(mode, "a") == 0)
  {
    flags = O_WRONLY | O_CREAT | O_APPEND;
  }
  else if (strcmp(mode, "a+") == 0)
  {
  }

  int fd = open(filename, flags, 0666);
  if (fd < 0)
    return NULL;

  MyFILE *pf = (MyFILE *)malloc(sizeof(MyFILE));
  if (pf == NULL)
    return NULL;

  memset(pf, 0, sizeof(MyFILE));

  pf->_fd = fd;
  pf->_end = 0;
  pf->_flags = LINE_FLUSH;
  return pf;
}

void my_fclose(MyFILE *pf)
{
  assert(pf);
  my_fflush(pf);
  close(pf->_fd);
  free(pf);
}

void my_fwrite(MyFILE *pf, char *buffer, int len)
{
  assert(pf);
  assert(buffer);
  assert(len >= 0);

  // 写入到缓冲区 认为 不会填满
  strncpy(pf->_buffer + pf->_end, buffer, len); // 写入到 buffer中的_end的位置
  pf->_end += len;

  // 开始 刷新
  if (pf->_flags & NONE_FLUSH)
  {
  }
  else if (pf->_flags & LINE_FLUSH)
  {
    // 只要是行缓冲肯定是 '\n'
    // abcd\n
    if (pf->_end > 0 && pf->_buffer[pf->_end - 1] == '\n')
    {
      // 给我刷新 写入到内核中
      write(pf->_fd, pf->_buffer, pf->_end);
      pf->_end = 0;
      syncfs(pf->_fd);
    }
  }
  else if (pf->_flags & FULL_FLUSH)
  {
  }
}
int main()
{

  MyFILE *pf = my_fopen("log.txt", "w");
  char *s = "aaaaaaa\n";
  my_fwrite(pf, s, strlen(s));
  fork();
  my_fclose(pf);

  return 0;
}
// int main()
// {

//   MyFILE *pf = my_fopen("log.txt", "w");
//   char *s = "aaaaaaa";
//   my_fwrite(pf, s, strlen(s));
//   fork();
//   my_fclose(pf);

//   return 0;
// }

// int main()
// {

//   MyFILE *pf = my_fopen("log.txt", "w");
//   if (pf == NULL)
//   {
//     printf("my_fopen errno\n");
//     return 1;
//   }
//   char *s = "hello my file\n";
//   my_fwrite(pf, s, strlen(s));
//   printf("消息已经刷新\n");

//   char *ss = "hello my file 1";
//   my_fwrite(pf, ss, strlen(ss));
//   printf("写了一个不满足刷新的字符串\n");
//   sleep(5);

//   char *sss = "hello my file 2";
//   my_fwrite(pf, sss, strlen(sss));
//   printf("写了一个不满足刷新的字符串\n");
//   sleep(5);

//   my_fclose(pf);

//   return 0;
// }

// typedef struct MyFILE
// {
//   int _fd;
//   char _buffer[NUM];
//   int _flags; // 刷新策略
//   int _end;   // buffer的结尾
// } MyFILE;
// void my_fflush(MyFILE *pf)
// {
//   assert(pf);
//   if (pf->_end > 0)
//   {
//     write(pf->_fd, pf->_buffer, pf->_end);
//     pf->_end = 0;
//     syncfs(pf->_fd);
//   }
// }
// MyFILE *my_fopen(char *filename, char *mode)
// {
//   assert(filename);
//   assert(mode);
//   int flags = O_RDONLY;
//   if (strcmp(mode, "r") == 0)
//   {
//   }
//   else if (strcmp(mode, "r+") == 0)
//   {
//   }
//   else if (strcmp(mode, "w") == 0)
//   {
//     flags = O_WRONLY | O_CREAT | O_TRUNC;
//   }
//   else if (strcmp(mode, "w+") == 0)
//   {
//   }
//   else if (strcmp(mode, "a") == 0)
//   {
//     flags = O_WRONLY | O_CREAT | O_APPEND;
//   }
//   else if (strcmp(mode, "a+") == 0)
//   {
//   }

//   int fd = open(filename, flags, 0666);
//   if (fd < 0)
//     return NULL;

//   MyFILE *pf = (MyFILE *)malloc(sizeof(MyFILE));
//   if (pf == NULL)
//     return NULL;

//   memset(pf, 0, sizeof(MyFILE));

//   pf->_fd = fd;
//   pf->_end = 0;
//   pf->_flags = LINE_FLUSH;
//   return pf;
// }

// void my_fclose(MyFILE *pf)
// {
//   assert(pf);
//   my_fflush(pf);
//   close(pf->_fd);
//   free(pf);
// }

// void my_fwrite(MyFILE *pf, char *buffer, int len)
// {
//   // if(pf == NULL)
//   // {
//   // printf("--------------\n");
//   // printf("111111111\n");
//   // }

//   assert(pf);
//   assert(buffer);
//   assert(len >= 0);
//   printf("--------------\n");

//   // 写入到缓冲区 认为 不会填满
//   strncpy(pf->_buffer + pf->_end, buffer, len); // 写入到 buffer中的_end的位置
//   pf->_end += len;

//   // 开始 刷新
//   if (pf->_flags & NONE_FLUSH)
//   {
//   }
//   else if (pf->_flags & LINE_FLUSH)
//   {
//     // 只要是行缓冲肯定是 '\n'
//     // abcd\n
//     if (pf->_end > 0 && pf->_buffer[pf->_end - 1] == '\n')
//     {
//       // 给我刷新 写入到内核中
//       write(pf->_fd, pf->_buffer, pf->_end);
//       pf->_end = 0;
//       syncfs(pf->_fd);
//     }
//   }
//   else if (pf->_flags & FULL_FLUSH)
//   {
//   }
// }

// int main()
// {
//   //printf("--------------\n");

//   MyFILE *pf = my_fopen("log.txt", "w");
//   if (pf == NULL)
//   {
//     printf("my_fopen errno\n");
//     return 1;
//   }
//   char *s = "hello my file\n";
//   my_fwrite(pf, s, strlen(s));

//   my_fclose(pf);
//   printf("--------------\n");
//   return 0;
// }

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
