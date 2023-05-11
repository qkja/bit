/**
 * User: Qkj
 * Description: KMP 算法
 * Date: 2023-05-11
 * Time: 16:40
 */
#include <vector>
#include <string>
void getNext(const std::string &str, std::vector<int> &next)
{
  // 这里是有问题的
  next[0] = -1;
  next[1] = 0;
  int k = 0;
  int i = 2;

  for (; i < str.size();)
  {
    if (k == -1 || str[i - 1] == str[k])
    {
      next[i] = k + 1;
      i++; // 为何这里i++
      k++; // k = next[i]; 这里才是我们本质
    }
    else
    {
      k = next[k];
    }
  }
}

int KMP(const std::string &str, const std::string &sub, int pos)
{
  if (str.empty() || sub.empty())
    return -1;
  // pos 合肥行判断
  int lenStr = str.size();
  int lenSub = sub.size();

  if (pos < 0 || pos >= lenStr)
    return -1;

  int i = pos; // 主串便利
  int j = 0;   // 字串便利

  std::vector<int> next;
  next.resize(lenSub, -1);
  getNext(sub, next);

  while (i < lenStr && j < lenSub)
  {
    if (j == -1 || str[i] == sub[j])
    {
      // 这里有点错误
      i++;
      j++;
    }
    else
    {
      j = next[j]; // 回退
    }
  }

  if (j >= lenSub)
  {
    return i - j; //
  }
  else
  {
    return -1;
  }
}

#include <iostream>

int main()
{
  std::cout << KMP("ababcabcdabcde", "abcd", 0) << std::endl;
  std::cout << KMP("ababcabcdabcde", "abcde", 0) << std::endl;
  std::cout << KMP("ababcabcdabcde", "abcdef", 0) << std::endl;
  return 0;
}