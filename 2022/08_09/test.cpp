#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> v(10,1);
	vector<int>::iterator pos = v.begin();
	int i = 0;
	while (i < 100)
	{
    if(i == 10)
    {
      cout << "测试" << endl;
    }
		cout << i << endl;
		v.insert(pos, 2);
		i++;
	}
	return 0;
}
