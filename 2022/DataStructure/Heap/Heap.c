#include "Heap.h"
static void swap(int *pa, int *pb)
{
  assert(pa);
  assert(pb);
  int ret = *pa;
  *pa = *pb;
  *pb = ret;
}
void HeapSort(int *arr, int len)
{
  // 建堆
  for (int parent = (len - 1 - 1) / 2; parent >= 0; parent--)
  {
    /* code */
    adjustDown(arr, len, parent);
  }

  // 建好了堆  这里开始去数字
  // 见了小堆 -->堆顶元素最小 我们把元素放在最后一个元素   这里算是降序
  for (size_t i = len-1; i > 0; i--)
  {
    //123 -- 3
    swap(&arr[0], &arr[i]);
    adjustDown(arr, i, 0);
  }
}

HPDataTytpe HeapTop(Heap *php)
{
  assert(php);
  if (HeapEmpty(php))
    assert(false);
  return php->elem[0];
}

void adjustDown(HPDataTytpe *elem, int size, size_t root)
{
  assert(elem);
  int parent = root;
  int child = root * 2 + 1;

  while (child < size)
  {
    // 找到左右孩子比较小的
    if (child + 1 < size && elem[child + 1] < elem[child])
      child++;

    if (elem[child] < elem[parent])
      swap(&elem[child], &elem[parent]);
    else
      break;

    parent = child;
    child = parent * 2 + 1;
  }
}

bool HeapEmpty(Heap *php)
{
  assert(php);
  return php->szie == 0;
}

void HeapPop(Heap *php)
{
  assert(php);
  if (HeapEmpty(php))
  {
    return;
  }
  //交换 堆顶  和  堆 尾
  swap(&(php->elem[0]), &(php->elem[php->szie - 1]));
  php->szie--;
  //向下调整
  adjustDown(php->elem, php->szie, 0);
}
//向上调整
void adjustUp(HPDataTytpe *elem, int size)
{
  assert(elem);
  // 注意size是最后一个元素的下一个素
  int parent = (size - 2) / 2;
  int child = size - 1;
  while (child > 0)
  // while (parent >= 0)
  {
    if (elem[parent] > elem[child])
      swap(&elem[parent], &elem[child]);
    else
      break;
    child = parent;
    parent = (child - 1) / 2;
  }
}

void HeapPush(Heap *php, HPDataTytpe val)
{
  assert(php);
  //判满 -- 这里就不简单的疯转成一个函数了
  if (php->capacity == php->szie)
  {
    size_t newSize = (php->capacity == 0) ? 4 : 2 * (php->capacity);
    HPDataTytpe *pCur = (HPDataTytpe *)realloc(php->elem, sizeof(HPDataTytpe) * newSize);
    assert(pCur);
    php->elem = pCur;
    php->capacity = newSize;
  }

  php->elem[php->szie++] = val;
  adjustUp(php->elem, php->szie); // 向上调整
}

// 初识化
void HeapInit(Heap *php)
{
  assert(php);
  php->elem = NULL;
  php->capacity = 0;
  php->szie = 0;
}

// 销毁堆
void HeapDestroy(Heap *php)
{
  assert(php);
  free(php->elem);
  php->elem = NULL;
  php->capacity = 0;
  php->szie = 0;
}
