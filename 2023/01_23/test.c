/**
* User: Qkj
* Description: 
* Date: 2023-01-23
* Time: 10:16
*/
#include <stdio.h>




//const int flag = 1;
 int flag = 1;


int main()
{
	int* p = &flag;
	while (flag)
	{
		printf("%d \n", flag);
		*p = 0;
	}
	printf("-------------");

	return 0;
}












//int main()
//{
//	char* p = "hello";//常量字符串
//	*p = 'H';
//    printf("%c", p);
//	return 0;
//}
