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
  umask(0);

  close(1);
  int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (fd < 0)
  {
    printf("%s\n", strerror(errno));
    exit(1);
  }
  char* p = "123";
  write(stdout->_fileno, p,3);
 // printf("fd %d\n", fd);
 // fflush(stdout);
  close(fd);
  return 0;
}
