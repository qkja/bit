#include <iostream>
#include <unistd.h>

using namespace std;
int g_val = 10;

int main()
{
  pid_t id = fork();
  if(id == 0)
  {
    // parent
    printf("我是父进程 %d\n",g_val);
  }
  else 
  {
    // child
    printf("我是子进程 %d\n",g_val);
  }
  return 0;
}
