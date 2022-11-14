/**
* User: Qkj
* Description: 
* Date: 2022-11-14
* Time: 14:21
*/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
  
  printf("hello printf"); // stdout 中写

  const char* msg = "hello write";

  write(1, msg, strlen(msg));
  sleep(5);


























  //int fd = open("log.txt", O_RDONLY | O_CREAT, 0666);
  //if(fd < 0)
  //{
  //  printf("%s\n", strerror(errno));
  //  exit(1);
  //}
  //int ret = dup2(fd, 0);
  //if(ret >= 0)
  //{
  //  close(fd);
  //}

  //char buffer[64];

  //while(fgets(buffer, sizeof(buffer), stdin) != NULL)
  //{
  //  printf("%s\n",buffer);
  //}


  //int ret = dup2(fd, 1);
  //int ret = dup2(fd, 1);

  //int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
  //int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);

  //if(dup2(fd,1) > 0)
  //{
  //  close(1);
  //}
  ////dup2(fd, 1); // 这么传  







  //printf("ret %d\n", ret);
  //printf("打开文件成功 fd %d\n",fd);

















  //fprintf(stdout, "%s %d\n","打开文件成功",fd);

  //fflush(stdout);
  //close(fd);


  //printf("stdin %d\n", stdin->_fileno);
  //printf("stdout %d\n", stdout->_fileno);
  //printf("stderr %d\n", stderr->_fileno);

  //const char* msg = "123456\n";

  //write(1, msg, strlen(msg));
  //write(2, msg, strlen(msg));


//int main()
//{
//  umask(0);
//  char buffer[128];
//
//  ssize_t s = read(0, buffer, sizeof(buffer)-1);

//  if(s > 0)
//  {
//    buffer[s] = '\0';
//    printf("输出 %s", buffer);
//  }



  //write(0, msg, strlen(msg));

















  //int fda = open("loga.txt", O_WRONLY|O_CREAT, 0666);
  //int fdb = open("logb.txt", O_WRONLY|O_CREAT, 0666);
  //int fdc = open("logc.txt", O_WRONLY|O_CREAT, 0666);
  //int fdd = open("logd.txt", O_WRONLY|O_CREAT, 0666);
  //int fde = open("loge.txt", O_WRONLY|O_CREAT, 0666);


  //printf("fda %d\n", fda);
  //printf("fdb %d\n", fdb);
  //printf("fdc %d\n", fdc);
  //printf("fdd %d\n", fdd);
  //printf("fde %d\n", fde);
  return 0;
}














//int main()
//{
//  umask(0);
//  //int fd = open("file.txt",O_WRONLY | O_CREAT | O_TRUNC,0666);
//  // 读文件
//  int fd = open("file.txt", O_RDONLY, 0666);
//
//  if(fd < 0)
//  {
//    printf("%s\n",strerror(errno));
//    exit(1);
//  }
//
//  printf("fd %d\n", fd);
//  char buffer[128];
//
//  ssize_t s = read(fd, buffer, sizeof(buffer)-1); // w我们希望是  字符串
//  // 这里是 一个字节来读
//  if(s > 0)
//  {
//    buffer[s-1] = '\0';  // 这个注意下标
//    printf("%s\n", buffer);
//  }
//
//
//
//
//  //printf("fd %d\n", fd);
//  ////printf("打开文件成功\n");
//  ////const char* str = "hello bit\n";
//  //const char* str = "aaa";
//  //int len = strlen(str);
//  ////printf("%d\n",len);
//  //int cnt = 5;
//  //while(cnt--)
//  //{
//  //  //ssize_t s =  write(fd, str, len);  // 注意  带 \0 是C语言的风格  
//  //  write(fd, str, len);  // 注意  带 \0 是C语言的风格  
//  //}
//
//
//  return 0;
//}
