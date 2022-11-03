/** 
 * Author       : Qkj
 * Description  : system V
 * Date         : 2022-11-02 19:16:01
 * LastEditTime : 2022-11-03 17:39:43
 */

// 通信的一种方式    
// 创建/销毁共享内存
// 关联/去关联 

// 记住通信的前提 是必须看到一份资源

// shmget()
// 参数3   IPC_CREAT　IPC_EXCL


//  函数认识
// key -> 生成 ftok 

// 存在那里 ? 内核中    OS会对 共享内存做管理  key 出现了 内核的唯一值
// 

// int main()

// {

//     return 0;
// }

#include <string>
#include <iostream>
using namespace std;

// int main()
// {
//     string floweredCloth;
//     string trim;

//     while(cin >> floweredCloth >> trim)
//     {
//         // cout << floweredCloth << endl;
//         // cout << trim << endl;

//         // 这里直接记录 饰条的第一个字符  
//         // char ch = trim[0];
//         // int len = trim.size(); // 记录饰条的长度
//         // int pos = 0;
//         // pos 
//         // while(1)
//         // {

//         // }

//         //size_t find (const string& str, size_t pos = 0) const;
//         int pos = floweredCloth.find(trim,0);
//         int len = trim.size();
//         int count = 0;
//         while(pos != string::npos)
//         {
//             count++;
//             pos = floweredCloth.find(trim, pos + len);
//         }

//         cout << count << endl;

//     }

//     return 0;
// }
// int fib(int n)
// {
//     if(n < 3)
//         return 1;
//     int left = 1;
//     int right = 1;
//     int sum = left +right;
//     for(int i = 3; i < n; i++)
//     {
//         left = right;
//         right = sum;
//         sum = left +right;
//     }
//     return sum;
// }
// int main()
// {
//     int from = 0;
//     int to = 0;
//     while (cin >> from >> to)
//     {
//        int sum = 0;
//        for(int i = from; i <= to; i++)
//        {
//         sum += fib(i);
//        }
//        cout << sum << endl;
//     }
    
//     return 0;
// }