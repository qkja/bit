#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> v(10,1);
	vector<int>::iterator it = v.begin();
	cout << v.capacity() << endl;
  v.erase(it);
	*it;
	return 0;
}
