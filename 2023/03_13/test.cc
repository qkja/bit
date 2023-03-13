/**
 * User: Qkj
 * Description:
 * Date: 2023-03-13
 * Time: 10:00
 */

// int main()
// {
//   int b = 0;
//   int &&c = b;
//   // 10;
//   // int&& a = 10; // 右值引用
//   return 0;
// }

#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;

template <class F, class T>
T useF(F f, T x)
{
  static int count = 0;
  cout << "count:" << ++count << endl;
  cout << "count:" << &count << endl;
  return f(x);
}
double f(double i)
{
  return i / 2;
}
struct Functor
{
  double operator()(double d)
  {
    return d / 3;
  }
};
int main()
{
  // 函数名
  cout << useF(f, 11.11) << endl; // count:1 count:0025C140  5.555
  // 函数对象
  cout << useF(Functor(), 11.11) << endl; // count:1 count: 0025C144 3.70333
  // lamber表达式
  cout << useF([](double d) -> double
               { return d / 4; },
               11.11)
       << endl; // count : 1 count: 0025C148 2.7775
  return 0;
}

// struct Goods
// {
//   string _name;
//   double _price;
// };
// int main()
// {
//   Goods gds[] = {{"苹果", 2.1}, {"相交", 3}, {"橙子", 2.2}, {"菠萝", 1.5}};
//   sort(gds, gds + sizeof(gds) / sizeof(gds[0]), [](Goods g1, Goods g2) -> bool
//                                                 { return g1._price <= g2._price; });
//   return 0;
// }

// #include <algorithm>
// #include <functional>
// struct Goods
// {
//   string _name;
//   double _price;
// };
// struct Compare
// {
//   bool operator()(const Goods &gl, const Goods &gr)
//   {
//     return gl._price <= gr._price;
//   }
// };
// int main()
// {
//   Goods gds[] = {{"苹果", 2.1}, {"香蕉", 3}, {"橙子", 2.2}, {"菠萝", 1.5}};
//   sort(gds, gds + sizeof(gds) / sizeof(gds[0]), Compare());
//   return 0;
// }

// int main()
// {
//   int array[] = {4, 1, 8, 5, 3, 7, 0, 9, 2, 6};
//   std::sort(array, array + sizeof(array) / sizeof(array[0]), greater<int>());
//   for(auto& e:array)
//   {
//     cout << e <<" ";
//   }
//   cout << endl;
//   return 0;
// }