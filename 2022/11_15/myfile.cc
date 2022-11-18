/**
* User: Qkj
* Description: 
* Date: 2022-11-15
* Time: 21:39
*/
#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
  // 标准输出  -- cout 1
  // 标准输出  -- cerr 2
  
  // 但是都是显示器 有什么区别
  
  // stdout 
  printf("hello printf 1\n");  // 1
  fprintf(stdout,"hello fprintf 1\n");
  fputs("hello fputs 1\n", stdout);

  // stderr
  
  fprintf(stderr,"hello fprintf 2\n");
  fputs("hello fputs 2\n", stderr);
  perror("hello perror 2");

  // cout 
  cout << "hello cout 1" << endl;

  //cerr
  cerr << "hello cerr 2" << endl;
  return 0;
}
