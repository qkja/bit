#include <stdio.h>
int g_val1 = 1;
int g_val2 = 1;

int main()
{
	printf("&g_val1 %p\n", &g_val1);
	printf("&g_val2 %p\n", &g_val2);

	return 0;
}
//int main()
//{
//	/*printf("&g_val1 %p\n", &g_val1);
//	printf("&g_val2 %p\n", &g_val2);*/
//	if (&g_val1 > &g_val2)
//	{
//		printf("aaaaaa\n");
//	}
//	return 0;
//}



//int g_val1;
//int g_val2;
//int main()
//{
//	printf("&g_val1 %p\n", &g_val1);
//	printf("&g_val2 %p\n", &g_val2);
//	return 0;
//}
