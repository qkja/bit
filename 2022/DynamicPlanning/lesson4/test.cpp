/** 
 * Author       : Qkj
 * Description  : 算法课 第四节
 * Date         : 2022-11-01 19:30:40
 * LastEditTime : 2022-11-01 20:35:35
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// 回文字符串分割
// 状态  f(i)  表示 前 i 个字符的最小分割次数
// 如何利用 f(i-1) 的结果   我们需要看 所有的情况  
// 前面的i-1个字符我不管 我们需要看看整体是不是回文串不是+1,是就是0
// f(i) = 
//  学会使用具体的情况分析问题
class Solution {
public:
    /**
     * 判断回文字符串
     * @param s string字符串 
     * @return int整型
     */
    bool IsReply(const string& str)
    {
        int left = 0;
        int right = str.size()-1;
        while(left < right)
        {
            if(str[left] != str[right])
                return false;
            left++;
            right--;
        }
        return true;
    }

    int minCut(string s) {
        // write code here
        if(s.empty())
            return -1;
        int len = s.size();
        vector<int> result;
        result.resize(len+1);
        result[0] = 0;
        result[1] = 0;


        for (size_t i = 2; i < len+1; i++)
        {
            result[i] = i-1; // 先给一最大值
            // 先判断整体
            if(IsReply(s.substr(0,i)))
            {
                result[i] = 0;
                continue;
            }
            // i = 3  j = 1
            // aab
            for (size_t j = 1; j < i; j++)
            {

                string str = s.substr(j, i-j);
                // a        ab
                //aa // b
                if(IsReply(str))
                {
                    // 这里是回文
                    // 2
                    int len = result[j] + 1;
                    if(len < result[i])
                        result[i] = len;
                }
            }
            
        }
        return result[len];
    }
};

int main()
{
    string str = "aaa";
    cout << Solution().minCut(str) << endl;
    return 0;
}


// f(1) = 0 f(0) = 1
// class Solution {
// public:
//     /**
//      * 
//      * @param s string字符串 
//      * @return int整型
//      */
//     bool IsReply(string str)
//     {
//         int left = 0;
//         int right = str.size()-1;
//         while(left < right)
//         {
//             if(str[left] != str[right])
//                 return false;
//             left++;
//             right--;
//         }
//         return true;
//     }

//     int minCut(string s) {
//         // write code here
//         if(s.empty())
//             return -1;
//         int len = s.size();
//         vector<int> result;
//         result.resize(len+1);
//         result[0] = 0;
//         result[1] = 0;
//         for(int i = 2; i < len + 1; i++)
//         {
//             int min = i-1;
//             cout << min << endl;

//             for(int j = 0; j < i; j++)
//             {
//                 // 开始切割
//                 string str = s.substr(j, i-j);
//                 int len = 0;
//                 if(!IsReply(str))
//                     len++;

//                 if(result[j]+len < min)
//                 {
//                     min = result[j]+len;
//                 }
//             }
//             //cout << min << endl;

//             result[i] = min;
//         }
//         //cout << len << endl;
//         return result[len];
//     }
// };

// int main()
// {
//     string str = "ab";
//     cout << Solution().minCut(str) << endl;
//     return 0;
// }



// 对于背包问题  
// f(i,j)   i表示要放i个物品.j表示背包的容量  V表示体积 A表示价值 
// 可以放
//  选择不放    f(i-1,j)
//  选择放  也有两个选则   
//  直接放  和拿
//  出来一部分放总体  f(i-1, j-V[i-1])+A[i-1]        
//不能放  
// 这个由于当前体积大于容量

// 初始化  f(0,j)  ==  0  f(i,0) == 0
// class Solution {
// public:
//     /**
//      * @param m: An integer m denotes the size of a backpack
//      * @param a: Given n items with size A[i]
//      * @param v: Given n items with value V[i]
//      * @return: The maximum value
//      */
//     int backPackII(int m, vector<int> &a, vector<int> &v) {
//         // write your code here
//         //f(i,j)   i表示要放i个物品.j表示背包的容量
//         int row = a.size()+1;
//         int col = m+1;
//         int result[row][col] = {0};
//         for (size_t i = 1; i < row; i++)
//         {
//             for (size_t j = 1; i < col; i++)
//             {
//                 if(A[i-1] <= j)
//                 {
//                     // 可以放进去
//                     result[i][j] = max(result[i-1,j],result[i-1,j-a[i-1]]+v[i-1]);
//                 }
//                 else 
//                 {
//                     result[i][j] = result[i-1,j];
//                 }
//             }
//         }
//         return result[row-1][col-1];
//     }
// };