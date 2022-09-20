#include <stdio.h>
int main()
{
  // 变量的 创建是需要开辟空间的
  // 1 byte = 8 bit
  // 1 MB = 1024 * 1024 byte
  // 1 G = 1024MB = 10亿字节  80多亿比特位
  // 类型的作用是用来创建变量的
  //int age; // 不好的行为
  //printf("%d",age);
  //全局变量和局部变量的  在代码块的那里 

  return 0;
}

// 编译器的分类
// 我们用的VS系列,叫做集成开发环境,底层的编器 是msvc
// 现在用的是gcc ,在Linux环境下
// 常见的还有 clang... 这里就不罗嗦了
// C语言之前 叫做 低级语言  是用法低级,不是功能低级

// main 函数是程序的入口
// main 函数不带返回,坚决抵制  函数不带返回,默认是int
// 还有 不要 void main 还不带return 0,这就是垃圾

//int main()
//{
//  // 打印函数 格式化  "" 是字符串 这是语法
//  // 一个库函数,在stdio.h 里面  这就是 我们包含 库函数的原因
//  printf("Hello world\n");
//
//  // 写代码 是为了 解决问题,我们首先要描述问题 这就是数据的来源,比如说是整数,小鼠,字符串
//  // 这就是我们数据类型
//  // 定义整型的时候,你要给他初始化  推荐
//
//  int a = 0;
//  float f = 1.0f;  // 小数默认是  double  我们最好带一个 f
//  double d = 10.0;
//  extern int ff;
//  printf("%d\n",sizeof(ff)); //  问题
//  printf("%d\n",&ff); //  问题
//  printf("Hello world\n");
//  return 0;
//}
