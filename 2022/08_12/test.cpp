#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  while(1)
  {
    printf("I am a process. pid : %d\n",getpid());
    sleep(1);

  }
  return 0;
}
