#include <iostream>
#include <queue>
using namespace std;
int main()
{
    int myints[]= {10,60,50,20};
    std::priority_queue<int> first;
     for(auto ch:myints)
    {
       first.push(ch);
    }
     while(!first.empty())
     {

       cout << first.top() <<" ";
       first.pop();
     }
   
   return 0;
}
