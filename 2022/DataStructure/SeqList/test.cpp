#include "SeqList.h"
void TestInit()
{

  SeqList s;
  SeqListInit(&s);
}

void TestPushBack()
{
  SeqList s;
  SeqListInit(&s);
  SeqListPushBack(&s, 1);
  SeqListPushBack(&s, 1);
  SeqListPushBack(&s, 1);
  SeqListPushBack(&s, 1);
  SeqListPushBack(&s, 2);

  SeqListPrint(&s);
  SeqListDestroy(&s);

}

int main()
{
  //TestInit();
  TestPushBack();
  return 0;
}
