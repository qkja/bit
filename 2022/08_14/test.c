#include <stdio.h>
#include <unistd.h>
int main()
{
  int val = 10;
  pid_t id = fork();
  if(id == 0)
  {
    // child
    while(1)
    {
      val = 20;
      printf("我是子进程 val = %d &val : %p\n",val ,&val);
      sleep(1);
    }
  }
  else 
  {
    while(1)
    {
      printf("我是父进程 val = %d &val : %p\n",val, &val);
      sleep(1);
    }
  }
  return 0;
}








/*int g_val;
int init_g_val = 1;
int main()
{
    printf("code        : %p\n",main);

    printf("init data   : %p\n",&init_g_val);
    printf("uninit data : %p\n",&g_val);

    char* array = (char*)malloc(10);

    static int a = 10;
    static int b;

    printf("init static : %p\n",&a);
    printf("static      : %p\n",&b);
    printf("heap area   : %p\n",array);
    printf("stack area  : %p\n",&array);


    free(array);
    return 0;
} */ 
