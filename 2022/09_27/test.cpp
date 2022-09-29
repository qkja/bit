#include <iostream>
#include <vector>
#include <string>
using namespace std;

class A
{
public:
	A()
		:_p(new int)
	{
		cout << "A()" << endl;
		*_p = 1;
	}
	A(const A& a)
		:_p(new int)
	{
		*_p = *a._p;
	}
	A& operator=(const A& a)
	{
		*_p = *a._p;
		cout << "A& operator=(const A& a)" << endl;

		return *this;
	}
	~A()
	{
		if (_p)
		{
			delete _p;
			_p = nullptr;
		}
		cout << "析构函数" << endl;
	}
private:
	int* _p;
};

int main()
{
	vector<A> v;
	A a1;
	A a2;
	A a3;
	A a4;
	v.push_back(a1);
	cout << "===============" << endl;

	v.push_back(a2);
	cout << "===============" << endl;

	v.push_back(a3);
	cout << "===============" << endl;

	v.push_back(a4);

	cout << "===============" << endl;
	return 0;
}


//class A
//{
//public:
//	A(int a = 0, int b = 0)
//		:_a(a)
//		, _b(b)
//	{
//		cout << "构造函数" << endl;
//	}
//	~A()
//	{
//		cout << "析构函数" << endl;
//	}
//private:
//	int _a;
//	int _b;
//};
//
//int main()
//{
//	A* pa1 = new A;
//	cout << "============" << endl;
//	A* pa2 = new A[4];
//
//	delete pa1;
//	delete[] pa2;
//	cout << "============" << endl;
//	return 0;
//}
