#include <stdio.h>
int fun( int a )
{
    int b = 0;
    static int c = 3;
    a = ( c ++,b ++ );
    return ( a );
}
int main( )
{
    int a = 2,i,k;
    for( i = 0;i<2;i ++ )
        k = fun( a ++ );
    printf("%d\n",k );
    return 0;
}



//int main()
//{
//  int x = 6;
//  x += x -= x * x;
//  printf("%d\n",x);
//  return 0;
//}
