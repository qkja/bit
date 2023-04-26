/**
* User: Qkj
* Description: 
* Date: 2023-04-26
* Time: 17:49
*/

#include <stdio.h>      
#include <unistd.h>      
      
int main()      
{      
  pid_t id = fork();  
  printf("hello bit id = %d\n",id);                                                                            
  sleep(1);                                                                                      
  return 0;                                                                                      
} 
