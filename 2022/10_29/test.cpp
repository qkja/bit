#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  ifstream ifs("test.cpp");
  char ch = '0';
  while(~(ch = ifs.get()))
  {
    
    cout << ch;
  }
  return 0;
}

// 解决 最后一个字符的问题
