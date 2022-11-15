/**
* User: Qkj
* Description: 
* Date: 2022-11-15
* Time: 13:21
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NUM 128
#define NONE_FLUSH 0x0
#define LINE_FLUSH 0x1
#define FULL_FLUSH 0x2

typedef struct _MyFILE 
{
  int _fd;
  char buffer[NUM];
  int _flags; // 刷新 标记位

  int _end; // 缓冲区的结尾
} MyFILE;

MyFILE* myFopen(const char* filename, const char* method)
{
  assert(filename);
  assert(method);
  int flags = O_RDONLY;
  if(strcmp(method, "w") == 0)
  {
    flags = O_WRONLY | O_CREAT | O_TRUNC;
  }
  else if(strcmp(method, "r"))
  {}
  else if(strcmp(method, "w+"))
  {}
  else if(strcmp(method, "r+"))
  {}
  else if(strcmp(method, "a"))
  {
    // 追加
    flags = O_WRONLY | O_CREAT | O_APPEND;
  }
  else if(strcmp(method, "a+"))
  {}
  else 
  {
    assert(0);
  }
  // 如果文件存在是另一种请款 这里不谈
  // 下面存在一个问题  如果打开文件失败,会出现 内存泄漏

  int fd = open(filename, flags, 0666);
  if(fd < 0)
    return NULL;

  MyFILE* fp = (MyFILE*)malloc(sizeof(MyFILE));
  if(fp == NULL)
    return fp;

  memset(fp, 0, sizeof(MyFILE));
  fp->_fd = fd;
  fp->_end = 0;
  fp->_flags |= LINE_FLUSH; // 这里默认是  行缓冲
  //if(fp->_fd < 0)
  //{
  //  return NULL;
  //}
  return fp;
}

void myFwrite(MyFILE* fp, const char* start, int len)
{
  assert(fp);
  assert(start);
  assert(len > 0);
  // 先写到 buffer 这里不考虑 满
  strncpy(fp->buffer+fp->_end, start, len);
  fp->_end += len;

  // a a \n
  if(fp->_flags & NONE_FLUSH)
  {}
  else if(fp->_flags & LINE_FLUSH)
  {
    // 行缓冲
    if(fp->_end > 0 && fp->buffer[fp->_end-1] == '\n')
    {
      write(fp->_fd, fp->buffer, fp->_end);
      fp->_end = 0;
      syncfs(fp->_fd); // 这个先不要关心这个接口
    }
  }
  else if(fp->_flags & FULL_FLUSH)
  {}
}

void myFFlush(MyFILE* fp)
{
  assert(fp);
  if(fp->_end > 0)
  {
    // 手动刷新
    write(fp->_fd, fp->buffer, fp->_end);
    fp->_end = 0;
    syncfs(fp->_fd); // 这个先不要关心这个接口
  }
}

void myFclose(MyFILE* fp)
{
  assert(fp);
  myFFlush(fp);
  close(fp->_fd);
  free(fp);
}

int main()
{
  MyFILE* fp = myFopen("log.txt", "w");
  if(fp == NULL)
  {
    printf("myFopen error\n");
    exit(1);
  }








  //const char* s = "hello my file\n";

  //myFwrite(fp, s, strlen(s));

  //myFclose(fp);
  //fp = NULL;
  return 0;
}
