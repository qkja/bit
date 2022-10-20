#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int Add(int num1, int num2) {
      int ret = num2;
      int anser = num1;
      while(ret != 0)
      {
        anser = num1 ^ num2;
        ret = (num1 & num2) << 1;
        num1 = anser;
        num2 = ret;
      }
      return anser;
    }
};






int main()
{
  int a = 0;
  int b = 0;
  int c = 0;
  vector<int> v;
  while(cin >> a>> b >> c)
  {
    v.clear();
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    sort(v.begin(), v.end());
    if(v[0]+v[1] > v[2] 
        &&v[2]-v[0] < v[1]
        &&v[2]-v[1] < v[0])
      cout << "Yes"<<endl;
    else 
      cout << "No" <<endl;
  }
  return 0;
}
