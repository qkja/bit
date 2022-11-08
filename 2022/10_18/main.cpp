#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
  std::cout << "PATH:" << getenv("PATH") << endl;
  std::cout << "MYPATH:" << getenv("MYPATH") << endl;
  cout << "Hello C++" << endl;
  cout << "Hello C++" << endl;
  cout << "Hello C++" << endl;
  cout << "Hello C++" << endl;
  cout << "Hello C++" << endl;
}






























//class Solution {
//public:
//    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
//      if(nums1.empty() || nums2.empty())
//        return;
//      int i = m - 1;
//      int j = n -1;
//      int desc = nums1.size() - 1;
//
//      while(i >= 0 && j>= 0)
//      {
//        if(nums1[i] <= nums2[j])
//        {
//          nums1[desc--] = nums2[j--];
//        }
//        else 
//        {
//          nums1[desc--] = nums1[i--];
//        }
//      }
//
//      if(i < 0)
//      {
//        for(i = 0; i <= j; i++)
//        {
//          nums1[i] = nums2[i];
//        }
//      }
//
//    }
//};
//

//class Solution {
//public:
//    // 这里我不确定 这个 vector 是否允许更改
//    void twoSumHelper(vector<int> nums, int target, vector<int>& result) {
//      sort(nums.begin(), nums.end());                           
//      int left = 0;
//      int right = nums.size() - 1;
//      while(left < right)
//      {
//        int sum = nums[left] + nums[right];
//        if(target == sum)
//        {
//          result.resize(2);
//          result[0] =nums[left];
//          result[1] = nums[right];
//          break;
//        }
//        else if(sum > target)
//        {
//          right--;
//        }
//        else
//        {
//          left++;
//        }
//      }
//    }
//    vector<int> twoSum(vector<int>& nums, int target) {
//      vector<int> result;
//      if(nums.empty())
//        return result;
//      twoSumHelper( nums, target, result);
//      if(!result.empty())
//      {
//          int left = result[0];
//          int right = result[1];
//          result.clear();
//          for(int i = 0 ;i < nums.size();i++)
//          {
//              if(left == nums[i] || right == nums[i])
//              {
//                  result.push_back(i);
//              }
//          }
//      }
//      return result;
//    }
//};


//int main()
//{
//  cout << "hello C++" << endl;
//  cout << "hello C++" << endl;
//  cout << "hello C++" << endl;
//  cout << "hello C++" << endl;
//  cout << "hello C++" << endl;
//  cout << "hello C++" << endl;
//  return 0;
//}

//long long NumberOfRoot(long long n)
//{
//    // 到这里的都是 大于10的
//    long long sum = 0;
//    while (n)
//    {
//        sum += n % 10;
//        n /= 10;
//    }
//    return sum;
//}
//int main()
//{
//    string str;
//    while (cin >> str)
//    {
//        // 这里把str 变成 int 
//        long long sum = 0;
//        for (char ch : str)
//        {
//            sum += (ch - '0');
//        }
//        while (sum > 9)
//        {
//            sum = NumberOfRoot(sum);
//        }
//        cout << sum << endl;
//    }
//    return 0;
//}

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
