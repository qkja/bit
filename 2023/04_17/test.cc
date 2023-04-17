/**
 * User: Qkj
 * Description:
 * Date: 2023-04-17
 * Time: 11:19
 */
#include <vector>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

// void Dfs(int index, int n, vector<int> &boxs, vector<int> &book)
// {
//   if (index == n + 1)
//   {
//     for (int i = 1; i <= n; i++)
//       cout << boxs[i] << " ";
//     cout << endl;
//     return; // 向上回退
//   }
//   for (int i = 1; i <= n; i++)
//   {
//     if (book[i] == 0) // 第i号牌仍在手上
//     {
//       boxs[index] = i;
//       book[i] = 1; // 现在第i号牌已经被用了
//       // 处理下一个盒子
//       Dfs(index + 1, n, boxs, book);
//       // 从下一个盒子回退到当前盒子，取出当前盒子的牌，
//       // 尝试放入其它牌。
//       book[i] = 0;
//     }
//   }
// }
// int main()
// {
//   int n;
//   vector<int> boxs;
//   vector<int> books;
//   cin >> n;
//   boxs.resize(n + 1, 0);       // 盒子
//   books.resize(n + 1, 0);      // 排
//   Dfs(1, n, boxs, books);
//   return 0;
// }
// #include <unordered_map>
// Definition for Employee.
// https://leetcode.cn/problems/employee-importance/submissions/
// class Employee
// {
// public:
//   int id;
//   int importance;
//   vector<int> subordinates;
// };

// class Solution
// {
// public:
//   int help(const std::unordered_map<int, Employee *> &m, const vector<Employee *> &employees, const Employee *ele)
//   {
//     int count = 0;
//     if (ele->subordinates.empty())
//     {
//       return ele->importance;
//     }

//     for (size_t i = 0; i < ele->subordinates.size(); i++)
//     {
//       int id = ele->subordinates[i];
//       auto it = m.find(id);
//       count += help(m, employees, it->second);
//     }

//     return ele->importance + count;
//   }

//   int getImportance(vector<Employee *> employees, int id)
//   {
//     if (employees.empty())
//       return -1;

//     std::unordered_map<int, Employee *> m;
//     for (auto &e : employees)
//     {
//       m[e->id] = e;
//     }
//     int count = help(m, employees, m[id]);
//     return count;
//   }
// };

// class Solution
// {
// public:
//   int help(const vector<Employee *> &employees, Employee *ele)
//   {
//     int count = 0;
//     if (ele->subordinates.empty())
//     {
//       return ele->importance;
//     }
//     for (size_t i = 0; i < ele->subordinates.size(); i++)
//     {
//       count += help(employees, getEmployee(employees, (ele->subordinates)[i]));
//     }
//     return ele->importance + count;
//   }

//   // 通过id 得到我们的员工信息
//   Employee *getEmployee(const vector<Employee *> &employees, int id)
//   {
//     for (auto &e : employees)
//     {
//       if (e->id == id)
//         return e;
//     }
//     return nullptr;
//   }
//   int getImportance(vector<Employee *> employees, int id)
//   {
//     if (employees.empty())
//       return -1;
//     Employee *ele = getEmployee(employees, id);
//     if (ele == nullptr)
//       return -1;
//     int count = help(employees, ele);
//     return count;
//   }
// };

class Solution
{
  vector<vector<int>> arr = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 上下左右
public:
  void Dfs(vector<vector<int>> &image, int row, int col,
           vector<vector<int>> &book, int x, int y,
           int newColor, int oldColor)
  {
    image[x][y] = newColor;
    book[x][y] = false;

    for (size_t i = 0; i < 4; i++)
    {
      // 四个位置
      int newX = x + arr[i][0];
      int newY = y + arr[i][1];

      if (!(newX >= 0 && newX < row && newY >= 0 && newY < col))
        continue;
      if (image[newX][newY] == oldColor && book[newX][newY] == true)
      {
        Dfs(image, row, col, book, newX, newY, newColor, oldColor);
      }
    }
  }

  vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
  {
    if (image.empty())
      return image;
    int old = image[sr][sc];
    int row = image.size();
    int col = image[0].size();
    vector<vector<int>> book(row, vector<int>(col, true));
    Dfs(image, row, col, book, sr, sc, color, old);
    return image;
  }
};