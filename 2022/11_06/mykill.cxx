/**
* User: Qkj
* Description: 
* Date: 2022-11-07
* Time: 09:18
*/
#include <iostream>           
#include <unistd.h>           
#include <signal.h>       
#include <stdlib.h>
#include <sys/types.h>                                              
using namespace std;   

void Usage()
{

}

int main(int argc, char* argv[])
{
  if(argc == 1)
  {
    cout << argv[0] << endl;
  }
  //if(argc != 3)
  //{
  //  Usage();
  //  exit(1);
  //}

  //if(-1 == kill((pid_t)atoi(argv[2]),atoi(argv[1])))
  //{
  //  // 出错
  //  exit(2);
  //}

  // 
  return 0;
}
