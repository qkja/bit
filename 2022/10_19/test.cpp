#include <iostream>
using namespace std;
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param number int整型 
     * @return int整型
     */
    int jumpFloorIIHelper(int number) {
    }
    int jumpFloorII(int number) {
        // write code here
    }
};


#include<iostream>
#include<cmath>
using namespace std;

int main() {
  int n;
  cin >> n;
  int tesult[20]  = {0};

  tesult[0] = 1;
  tesult[1] = 1;
  tesult[2] = 2;

  for (int i = 3; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      tesult[i] = tesult[i] + tesult[j];
    }
  }


  cout << tesult[n];


  return 0;
}

//int main() {
//    long double height = 0.0;
//    long double radius = 0.0;
//    const double PI = 3.14;
//    while (cin >> height >> radius) {
//        double cir = 2 * PI * radius;
//        if (height <= cir) {
//            cout << "Yes" << endl;
//        } else {
//            cout << "No" << endl;
//        }
//    }
//    return 0;
//}
