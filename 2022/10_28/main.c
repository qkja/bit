#include <stdio.h>

const char* f()
{
  return "abcd";
}

int main()
{

  

  char* p = f();
  printf("%s\n",p);


  // 这里我给一个结论 
  // 对于字符串 ""
  // 我们可以用char* 类型来接受 但是会报警告 这里杜绝修改字符串 它是在常量区的
  //
  //const char* p1 = NULL;
  //p1 = "abce";
  //printf("%s\n", p1);
  //printf("%d\n", (int)p1);

  //char* p2 = "abce";

  //printf("%s\n", p2);
  //printf("%d\n", (int)p2);


  //*p2 = 'd';

  //printf("%s\n", p1);
  //printf("%s\n", p2);


  // 这个方法不常用
  //char ch = 0;
  //ch = "abc"[1];
  //printf("%c\n", ch);
  return 0;
}


//int main()
//{
//
//
//  // 十六进制
//  //printf("%d",'\x123');
//
//
//  // 八进制 '\123' 第一个不是8的数子
//  // 并且他的长度不能超过三个
//  // 超过了三个应该是另外的一个意思 
//  // 至于是什么这就不太清楚了
//  //printf("%d\n",'\123');
//  //printf("%c\n",'\123');
//  //printf("%d\n",'\12');
//  //printf("%s\n","\1234");
//  return 0;
//}
//// 字符串字面量的换行的起始位置是前面不带任何一个空格
//int main()
//{
//  printf("aaaaaaaaaaaaaaaaaa\
//aaaaaaaaaaaaaaaaa\n");
//  printf("bbbbbbbbbbbbbbbbbb\
//          bbbbbbbbbbbbb\n");
//  return 0;
//}
