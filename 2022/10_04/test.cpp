#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:


  string LeftRotateString(string str, int n) {
   
   if(str.empty())
     return "";
   n = n % str.size();



  }
  // 滑动窗口的 问题
  //vector<vector<int> > FindContinuousSequence(int sum) {
  //  vector<vector<int>> vv;
  //  int low = 1;
  //  int high = 2;
  //  while(low < high)
  //  {
  //    //  求和  (a0 + an)*n/2
  //    int result = (low + high)*(high-low+1) / 2;
  //    if(sum == result)
  //    {
  //      vector<int> v;
  //      for(int i=low;i<=high;i++)
  //      {
  //        v.push_back(i);
  //      }
  //      vv.push_back(v);
  //      low++;
  //    }
  //    else if(sum > result)
  //    {
  //      high++;
  //    }
  //    else
  //    {
  //      low++;
  //    }
  //  }//endofwhile
  //  return vv;
  //}


  //struct myCompare
  //{
  //  bool operator()(int x, int y)
  //  {
  //    string sx = to_string(x);
  //    string sy = to_string(y);

  //    string A = sx;
  //    A += sy;

  //    string B = sy;
  //    B += sx;

  //    return A < B;
  //  }
  //};

  //void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
  //  if(data.empty())
  //    return;

  //  // 这需要 异或 一下  到底是 两个 x y的异或 结果一定不为0 可以以这个作为判据
  //  // 把这个  结果看作 二进制  一定有bit为1 这个位就是 x和y不同的位,
  //  // 我们准备两个数组,两两数据相同的一定在同一个数组,x y 在两个数组
  //  // 我们分别对这两个 数组异或 得到 xy
  //  int x = 0;
  //  *num1 = 0;
  //  *num2 = 0;

  //  for(auto& val : data)
  //    x ^= val;

  //  // 这里寻找 最后一个 位为1 
  //  int flag = 1;
  //  for(int i = 0; i < (int)sizeof(int)*8; i++)
  //  {
  //    
  //    if(x & (1<<i))
  //    {
  //      flag = 1 << i;
  //      break;
  //    }
  //  }

  //  for(size_t i = 0; i < data.size(); i++)
  //  {
  //    if(data[i] & flag)
  //      *num1 = (*num1) ^ data[i];
  //    else 
  //      *num2 = (*num2) ^ data[i];
  //  // 这里开始遍历
  //  }
  //}

  //string PrintMinNumber(vector<int> numbers) {
  //  if(numbers.empty())
  //    return "";

  //  sort(numbers.begin(), numbers.end(), myCompare());

  //  string str;
  //  for(auto& val : numbers)
  //    str += to_string(val);
  //  return str;
  //}


  // 连续子向量的和   就是 素组里面的连续元素
  // 定义:   f(i) : 表示 亿i下标结尾 的连续和
  // 转移:   f(i) = max(f(i-1)+arr[i], arr[i]);
  // 初始化: f(0) = arr[0]
  
  // 确立容器 一个一位数组
  
  // 方法二 优化一下 我们总是拿到 f(i-1)我们关系这个是不是负数
  //int FindGreatestSumOfSubArray(vector<int> array) {
  //  if(array.size() == 0)
  //    return 0;

  //  int total = array[0];
  //  int maxSum = total;
  //  for(size_t i = 1; i < array.size(); i++)
  //  {
  //    if(total >= 0)
  //      total += array[i];
  //    else 
  //      total = array[i];
  //    if(maxSum < total)
  //      maxSum = total;
  //  }
  //  return maxSum;
  //}

  // 方法一 简单的dp 3 + 1 1就是使用 一位数组还是二维数组
  //int FindGreatestSumOfSubArray(vector<int> array) {
  //  if(array.empty())
  //    return 0;

  //  int* dp = new int[array.size()]; // 这里初始化为0了
  //  dp[0] = array[0];
  //  int maxSum = dp[0];

  //  for(size_t i = 1; i < array.size(); i++)
  //  {
  //    dp[i] = max(dp[i-1]+array[i], array[i]);
  //    if(maxSum < dp[i])
  //      maxSum = dp[i];
  //  }

  //  delete[] dp;
  //  return maxSum;
  //}
};

//bool IsPalindrome(string &s, int *start, int *end)
//{
//
//  int left = 0;
//  int right = s.size() - 1;
//  bool result = true;
//  while(left < right)
//  {
//    if(s[left] != s[right])
//    {
//      result = false;
//      break;
//    }
//    else 
//    {
//      left++;
//      right--;
//    }
//  }
//
//  // 这里已经找到了
//  // 这是 碰到了 不能成为回文字符串的 两个节点  题目说了,去掉一个肯定可以的到 回文
//  if(start != nullptr)
//     *start = left;
//  if(end != nullptr)
//     *end = right;
//  return result;
//}
//
//int main() 
//{
//    int n = 0;
//    cin >> n;
//    while (n--) 
//    {
//      string s;
//      cin >> s;
//      int* start = new int(0); // 这里需要 
//      int* end = new int(0);
//      if(IsPalindrome(s, start, end))
//      {
//        cout << -1 << endl;
//      }
//      else 
//      {
//        // 这里需要输出下标
//        // 使用这个方法 比我想的要节省太多的空间
//        // 删除一个节点
//        // a b b 或者  b b a
//        s.erase(s.begin() + *start);
//
//        if(IsPalindrome(s, nullptr, nullptr))
//          cout << *start << endl;
//        else 
//          cout << *end << endl;
//        
//      }
//      delete start;
//      delete end;
//    }
//    return 0;
//}

