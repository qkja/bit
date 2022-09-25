#include <iostream>
#include <unordered_map>
using namespace std;
class Solution {
public:
  // 青蛙
  int jumpFloor(int number) {

  }
};





//class Solution {
//private:
//  unordered_map<int, int> m;
//public:
//  int Fibonacci(int n)
//  {
//    if(n == 0 || n == 1)
//      return n;
//    if(n == 2)
//      return 1;
//    int pprev = 0;
//    if(m.find(n-2) != m.end())
//    {
//      pprev = m[n-2];
//    }
//    else 
//    {
//      pprev = Fibonacci(n-2);
//      m[n-2] = pprev;
//    }
//    int prev = 0;
//    if(m.find(n-1) != m.end())
//    {
//      prev = m[n-1];
//    }
//    else 
//    {
//      prev = Fibonacci(n-1);
//      m[n-1] = prev;
//    }
//
//    return prev + pprev;
//  }
//
//  // 这个方法可以这么说,理解很容易,但是效率太低
//  // 充满了 大量的重复计算 函数栈帧就问题
//  //int Fibonacci(int n) {
//  //    if(n == 0)
//  //      return 0;
//  //    if(n <= 2)
//  //      return 1;
//  //    return Fibonacci(n-1) + Fibonacci(n-2);
//  //}
//
//  // 迭代法  动态规划 简单的
//  /*int Fibonacci(int n) {
//       if (n == 0)
//           return 0;
//       int first = 1;
//       int second = 1;
//       int sum = 0;
//       while (n > 2)
//       {
//           sum = first + second;
//           first = second;
//           second = sum;
//           --n;
//       }
//       return second;
//   }*/
//};
//
//int main()
//{
//  int n = 0;
//  std::cin >> n;
//  std::cout << Solution().Fibonacci(n) << std::endl;
//  return 0;
//}
