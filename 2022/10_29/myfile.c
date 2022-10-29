#include <stdio.h>
#include <assert.h>
#include <unistd.h>

int main()
{
  // 我们有意修改进程的工作路径
  //chdir("/home/bit/");
  //FILE* fp = fopen("log.txt","w");
  FILE* fp = fopen("log.txt","a");
  if(fp == NULL)
  {
    perror("fopen fail");
    return 0;
  }

  //printf("pid : %d\n", getpid());
  //while(1)
  //{
  //  sleep(1);
  //}
  const char* msg = "hello 104 ";
  int cnt = 1;
  while(cnt <= 5)
  {
    fprintf(fp, "%s: %d\n", msg, cnt++);
  }

  fclose(fp);
  fp = NULL;
  return 0;
}

  
//int main()
//{
//  FILE* fp = fopen("log.txt","r");
//  
//  assert(fp);
//  fclose(fp);
//  fp = NULL;
//  return 0;
//}
//


//int main()
//{
//  FILE* fp = fopen("log.txt","w");
//  if(fp == NULL)
//  {
//    perror("fopen fail");
//    return 0;
//  }
//
//  const char* msg = "hello 104 ";
//
//  int cnt = 1;
//  while(cnt <= 5)
//  {
//    fprintf(fp, "%s: %d\n", msg, cnt++);
//  }
//
//  fclose(fp);
//  fp = NULL;
//  return 0;
//}
