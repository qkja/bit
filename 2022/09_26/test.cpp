class Person
{
public:
	Person()
	{
		_age = 10;
	}
private:
	int _age;
};
class Student
{
public:

private:
	//int a;
	//int* p1;
	//short* p2;
	Person per;
	Person* pper1;
	Person* pper2;
};

int main()
{
	Student s;
	return 0;
}
