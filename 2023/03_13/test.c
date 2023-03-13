/**
* User: Qkj
* Description: 
* Date: 2023-03-13
* Time: 10:00
*/
#include <stdio.h>

    
int add(int a)    
{    
  int sum = 0;    
  int i = 0;    
  for(i=0;i<a;i++)                                                                                       
  {                                                
    sum += i;                                      
  }                                                
                                                   
  return sum;                                      
}                                                  
                                                   
int main()                                         
{                                                  
  int x = 10;                                      
  int total = add(x);                              
                                                   
  printf("%d\n",total);                            
  return 0;                                        
} 

















// class CParent
// {
// public:
//   virtual void Intro()
//   {
//     printf("I'm a Parent, ");
//     Hobby();
//   }
//   virtual void Hobby()
//   {
//     printf("I like football!");
//   }
// };
// class CChild : public CParent
// {
// public:
//   virtual void Intro()
//   {
//     printf("I'm a Child, ");
//     Hobby();
//   }
//   virtual void Hobby()
//   {
//     printf("I like basketball!\n");
//   }
// };
//#pragma pack(1)
//class CTest
//{
//public:
//  CTest() : m_chData('\0'), m_nData(0)
//  {
//  }
//  virtual void mem_fun() {}
//
//private:
//  char m_chData;
//  int m_nData;
//  static char s_chData;
//};
//char CTest::s_chData = '\0';
//int main(void)
//{
//  cout << sizeof(CTest) << std::endl;
//  // CChild *pChild = new CChild();
//  // CParent *pParent = (CParent *)pChild;
//  // pParent->Intro();
//  return (0);
//}
