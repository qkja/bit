
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
long long NumberOfRoot(long long n)
{
    // 到这里的都是 大于10的
    long long sum = 0;
    while (n)
    {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
int main()
{
    string str;
    while (cin >> str)
    {
        // 这里把str 变成 int 
        long long sum = 0;
        for (char ch : str)
        {
            sum += (ch - '0');
        }
        while (sum > 9)
        {
            sum = NumberOfRoot(sum);
        }
        cout << sum << endl;
    }
    return 0;
}

//#include <iostream>
//#include <stdio.h>
//#include <vector>
//using namespace std;
//int NumberOfRoot(int n)
//{
//  // 到这里的都是 大于10的
//  int sum = 0;
//  while(n)
//  {
//    sum += n%10;
//    n /= 10;
//  }
//  return sum;
//}
//int main()
//{
//  string str;
//  while(cin >> str)
//  {
//    // 这里把str 变成 int 
//    int sum = 0;
//    for(char ch: str)
//    {
//      sum += ch-'0';
//    }
//    cout << NumberOfRoot(sum) << endl;
//  }
//  return 0;
//}
//

//int main()
//{
//  int n = 0;
//  while(cin >> n)
//  {
//    while(n > 9)
//    {
//      n = NumberOfRoot(n);
//    }
//    cout << n << endl;
//  }
//  return 0;
//}


// 计算 斐波那契数列
// 1, 1  2
//int Fib(int n, vector<int>& v)
//{
//  if(n < 2)
//    return v[1];
//  int ans = v[n];
//  if(ans == 0)
//  {
//    // 这里使用缓存
//    ans = Fib(n-1, v) + Fib(n-2, v);
//  }
//  // 这里放入缓存表
//  v[n] = ans%10000;
//  return v[n];
//}
//
//int main()
//{
//  vector<int> v;
//  v.resize(10001);
//  v[0] = 1;
//  v[1] = 1;
//  int n = 0;
//  while(cin >> n)
//  {
//    for(int i = 0; i< n ;i++)
//    {
//      int ret = 0;
//      cin >> ret;
//      printf("%04d",Fib(ret, v));
//    }
//    printf("\n");
//  }
//  // 开辟相应数组的大小
//  
//}
