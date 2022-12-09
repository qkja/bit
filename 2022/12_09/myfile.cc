/**
 * Author       : Qkj
 * Description  :
 * Date         : 2022-12-09 17:41:44
 * LastEditTime : 2022-12-09 17:41:45
 */
#include <unistd.h>
#include <stdio.h>
int main()
{
  int pipefd[2] = {0};
  pipe(pipefd);
  printf("pipefd[0] %d\n", pipefd[0]);
  printf("pipefd[1] %d\n", pipefd[1]);
  return 0;
}