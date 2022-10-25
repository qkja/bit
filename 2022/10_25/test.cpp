#include <iostream>
#include <string>
#include <memory>

#include "SmartPtr.h"
using namespace std;

/*int div()
{
	int a, b;
	cin >> a >> b;
	if (b == 0)
		throw invalid_argument("除0错误");

	return a / b;
}

void func()
{
	int* p1 = new int[10]; // 这里亦可能会抛异常

	int* p2 = new int[10]; // 这里亦可能会抛异常
	int* p3 = new int[10]; // 这里亦可能会抛异常
	int* p4 = new int[10]; // 这里亦可能会抛异常

	try
	{
		div();
	}
	catch (...)
	{
		delete[] p1;
		delete[] p2;
		delete[] p3;
		delete[] p4;

		throw;
	}

	delete[] p1;
	delete[] p2;
	delete[] p3;
	delete[] p4;
}

int main()
{
	try
	{
		func();
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		// ...
	}

	return 0;
}*/

// 这里 有很大 问题就是和 异常有关

//int div()
//{
//	int a, b;
//	cin >> a >> b;
//	if (b == 0)
//		throw invalid_argument("除0错误");
//
//	return a / b;
//}
//
//void func()
//{
//	int* p1 = new int[10];
//	int* p2 = new int[10];
//  // 这里 
//  bit::SmartPtr<int> sp1(p1);
//  bit::SmartPtr<int> sp2(p2);
//
//  // 我们连异常都不用抛
//  div();
//
//}
//
//void func1()
//{
//  bit::SmartPtr<int> sp1(new int);
//  bit::SmartPtr<int> sp2(new int[3]);
//  bit::SmartPtr<int> sp4(sp1);
//
//  bit::SmartPtr<pair<string,int>> sp3(new pair<string,int>("sort", 1));
//
//  *sp1 = 1;
//  cout << *sp1 << endl;
//  
//  sp3->second++;  // 注意 这里应该是省略的一个 ->
//  cout << (*sp3).first << "  " << (*sp3).second << endl;
//  //cout << "===================" << endl;
//}
//
//int main()
//{
//  func1();
//  /*try
//	{
//		func();
//	}
//	catch (const exception& e)
//	{
//		cout << e.what() << endl;
//		// ...
//	}*/
//
//  //cout << "测试" << endl;
//	return 0;
//}


// 我们看一下 C++98提出的   指针指针
//int main()
//{
  // 这就是一个  神造作   禁止 管理权 转移 
  //std::auto_ptr<int> sp1(new int);
  //std::auto_ptr<int> sp2;
  //sp2 = sp1;
  //return 0;
//}

// 这里 unique_ptr 是一个
// 禁止拷贝的的指针
/*int main()
{
  unique_ptr<int> up1(new int);
  //unique_ptr<int>up2(up1);
  unique_ptr<int>up2;
  //up2 = up1;
  return 0;
}*/

// 总有场景需要拷贝
/*int main()
{
  shared_ptr<int> sp1(new int);
  shared_ptr<int> sp2(sp1);
  shared_ptr<int> sp3;
  sp3 = sp2;
  return 0;
}*/
