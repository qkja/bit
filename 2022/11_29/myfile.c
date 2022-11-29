/**
* User: Qkj
* Description: 
* Date: 2022-11-29
* Time: 20:54
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  umask(0);
  // 写文件
  int fd = open("bit",O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if(fd < 0)
  {
    printf("%s\n", strerror(errno));
    exit(1);
  }
  // 写文件
  const char* msg = "i like linux";
  write(fd, msg, strlen(msg));
  // 关闭文件
  close(fd);




  // 读文件
  fd = open("bit", O_RDONLY, 0666);
  if(fd < 0)
  {
    printf("%s\n", strerror(errno));
    exit(1);
  }
#define NUM 1024
  char buffer[NUM];
  memset(buffer, '\0', sizeof(buffer));
  int s = read(fd, buffer, NUM);
  if(s == 0)
  {
    printf("文件已经结尾了");
    exit(2);
  }
  // abcd
  buffer[s] = '\0';
  printf("%s\n", buffer);
  return 0;
}
