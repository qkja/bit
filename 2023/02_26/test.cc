/**
 * User: Qkj
 * Description:
 * Date: 2023-02-26
 * Time: 16:41
 */
#include <iostream>
#include "test.h"
using namespace std;
int main()
{
  A<int>a;
  a.func();
  return 0;
}


// int main()
// {
//   Swap<int>(1,2);
//   Swap<double>(1,2);
//   return 0;
// }

// template <class T1, class T2>
// class Data
// {
// public:
//   Data() { cout << "Data<T1, T2>" << endl; }

// private:
//   T1 _d1;
//   T2 _d2;
// };

// // 两个参数偏特化为指针类型
// template <typename T1, typename T2>
// class Data<T1 *, T2 *>
// {
// public:
//   Data() { cout << "Data<T1*, T2*>" << endl; }

// private:
//   T1 _d1;
//   T2 _d2;
// };

// int main()
// {
//   Data<int *, int *> d3; // 调用特化的指针版本
//   return 0;
// }

// template<class T>
// bool Less(T left, T right)
// {
// 	return left < right;
// }
// //   我们  把  Date* 在这个模板 给特殊化出来.
// template<>
// bool Less<int*>(int* left, int* right)
// {
//   cout << "Less<int*>" << endl;
// 	return *left < *right;
// }

// int main()
// {
//   int a = 0;
//   int b = 1;
//   cout << Less(&a,&b) <<endl;
//   return 0;
// }

// template<class T = int,typename K>
// T func(int n)
// {
// 	return n;
// }

// int main()
// {
// 	int ret = func<int>(10);
// 	cout << ret << endl;
// 	return 0;
// }

// template<class K = int,class V = char>
// void func()
// {
// 	cout << sizeof(K) << endl;
// 	cout << sizeof(V) << endl;
// }

// int main()
// {
// 	//func<int,double>();
// 	func();
// 	return 0;
// }

// template <class T>
// void Swap(T &left, T &right)
// {
//   T temp = left;
//   left = right;
//   right = temp;
// }
// int main()
// {
//   int a = 1;
//   int b = 2;
//   Swap(a, b);
//   cout << "a: " << a << "   b: " << b << endl;
//   return 0;
// }

// template <class T1, class T2>
// class Data
// {
// public:
//   Data() { cout << "Data<T1, T2>" << endl; }

// private:
//   T1 _d1;
//   T2 _d2;
// };

// template <>
// class Data<int, int>
// {
// public:
//   Data() { cout << "Data<int, int>" << endl; }

// private:
//   int _d1;
//   int _d2;
// };

// // 两个参数偏特化为指针类型
// template <typename T1, typename T2>
// class Data<T1 *, T2 *>
// {
// public:
//   Data() { cout << "Data<T1*, T2*>" << endl; }

// private:
//   T1 _d1;
//   T2 _d2;
// };
// // 两个参数偏特化为引用类型
// template <typename T1, typename T2>
// class Data<T1 &, T2 &>
// {
// public:
//   Data(const T1 &d1, const T2 &d2)
//       : _d1(d1), _d2(d2)
//   {
//     cout << "Data<T1&, T2&>" << endl;
//   }

// private:
//   const T1 &_d1;
//   const T2 &_d2;
// };
// void test2()
// {
//   Data<double, int> d1;        // 调用特化的int版本
//   Data<int, double> d2;        // 调用基础的模板
//   Data<int *, int *> d3;       // 调用特化的指针版本
//   Data<int &, int &> d4(1, 2); // 调用特化的指针版本
// }
// template <class T>
// void Swap(T &left, T &right)
// {
//   T temp = left;
//   left = right;
//   right = temp;
// }
// int main()
// {
//   int a = 1;
//   int b = 2;
//   Swap(a, b);
//   cout << "a: " << a << "   b: " << b << endl;

//   double d1 = 1.1111;
//   double d2 = 2.2222;
//   Swap(d1, d2);
//   cout << "d1: " << d1 << "  d2: " << d2 << endl;
//   return 0;
// }

// template <class T2>
// class Data<int, T2>
// {
// public:
// 	Data() {cout<<"Data<int, T2>" <<endl;}
// private:
// 	int _d1;
// 	T2 _d2;
// };

// int main()
// {
// 	Data<int, int> d1;
// 	return 0;
// }

// template<class T = int,typename K>
// T func(int n)
// {
// 	return n;
// }

// int main()
// {
// 	int ret = func<int,double>(10);
// 	cout << ret << endl;
// 	return 0;
// }

// template<class T>
// T add(const T& a, const T& b)
// {
// 	return a + b;
// }
// template<class T>
// T add( T& a, T& b)
// {
// 	return a + b;
// }
// int main()
// {

//   int ret = add<int>(1,2);
//   cout << ret << endl;
//   return 0;
// }

// int main()
// {
//   int a = 1;
//   int b = 2;
//   int ret = add(a,b);
//   cout << ret << endl;
//   return 0;
// }