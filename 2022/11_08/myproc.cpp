/**
* User: Qkj
* Description: 
* Date: 2022-11-07
* Time: 18:54
*/

#include <signal.h>
#include <iostream>
using namespace std;

int main()
{
  try 
  {
    int a = 0;
    if(a == 0)
      throw "异常";
  }
  catch(const char* e)
  {
    cout << e << endl;
  }
  return 0;
}


//void handler(int a)
//{
//  cout <<a <<endl;
//}
//int main()
//{
//
//  for(int i = 0; i < 31;i++)
//    signal(i+1, handler);
//
//  int a = 10;
//  a /= 0;
//
//  //  之前我们称 程序奔溃   楚玲错误 
//  //  进程奔溃的本质 是进程收到 异常信号
//  //  OS 怎么知道除磷   状态寄存器 的标志位会发什么改变
//
//  // 进程崩溃了 一定会导致进程种植吗  我们做的是默认行为
//  //int a = 10;
//  //a /= 0;
//
//  return 0;
//}
//
