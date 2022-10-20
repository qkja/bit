#include "SeqList.h"
//void TestInit()
//{
//
//  SeqList s;
//  SeqListInit(s);
//  printf("hello 数据结构");
//}

void TestInit()
{

  SeqList s ;
  SeqListInit(&s);
  printf("hello 数据结构");
}
int main()
{
  TestInit();
  return 0;
}









//void TestInit()
//{
//
//  SeqList s;
//  SeqListInit(&s);
//}
//
//void TestPushBack()
//{
//  SeqList s;
//  SeqListInit(&s);
//  SeqListPushBack(&s, 1);
//  SeqListPushBack(&s, 1);
//  SeqListPushBack(&s, 1);
//  SeqListPushBack(&s, 1);
//  SeqListPushBack(&s, 2);
//
//  SeqListPrint(&s);
//  SeqListDestroy(&s);
//
//}
