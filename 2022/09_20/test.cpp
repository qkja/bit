#include <iostream>
using namespace std;

class A
{
public:
	/*A(int a = 0)
	{
		cout << "构造函数" << endl;
	}*/
	A(int a,int b)
	{
		cout << "构造函数" << endl;
	}
	/*A()
	{
		cout << "构造函数" << endl;
	}*/
	/*A(const A& a)
	{
		cout << "拷贝构造" << endl;
	}*/
	int a;
	int b;
	int* p;
};

int main()
{
	int x = 0;

	A a1(1,2);
	a1.a = 1;
	a1.b = 1;
	a1.p = &x;
	A a2(a1);
	return 0;
}
