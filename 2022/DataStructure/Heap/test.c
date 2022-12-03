#include "Heap.h"

int main()
{
	int arr[] = { 4, 2, 7, 8, 5, 1, 0, 6 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	HeapSort(arr, sz);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}

// int main()
// {
// 	Heap heap;
// 	HeapInit(&heap);
// 	//int arr[] = {1, 4, 3, 5, 6, 22, 3, 4, 5};
// 	int arr[] = {1,2};
// 	int sz = sizeof(arr) / sizeof(arr[0]);
// 	HeapSort(arr, sz);
// 	for (int i = 0; i <sz; i++)
// 	{
// 		printf("%d ", arr[i]);
// 	}
// 	printf("\n");

// 	HeapDestroy(&heap);
// 	return 0;
// }

// int main()
// {
// 	Heap heap;
// 	HeapInit(&heap);
// 	int arr[] = {1, 4, 3, 5, 6, 22, 3, 4, 5};
// 	int sz = sizeof(arr) / sizeof(arr[0]);

// 	for (int i = 0; i < sz; i++)
// 	{
// 		HeapPush(&heap, arr[i]);
// 	}
// 	int index = 0;
// 	while (!HeapEmpty(&heap))
// 	{
// 		arr[index++] = HeapTop(&heap);
// 		HeapPop(&heap);
// 	}
// 	for (int i = 0; i < index; i++)
// 	{
// 		printf("%d ", arr[i]);
// 	}
// 		printf("\n");

// 	HeapDestroy(&heap);
// 	return 0;
// }

// int main()
// {
// 	Heap heap;
// 	HeapInit(&heap);
// 	HeapPush(&heap, 3);
// 	HeapPush(&heap, 5);
// 	HeapPush(&heap, 6);
// 	HeapPush(&heap, 10);
// 	HeapPush(&heap, 0);
//     //出堆
// 	HeapPop(&heap);
// 	for (int i = 0; i < (int)heap.szie; i++)
// 	{
// 		printf("%d ", heap.elem[i]);
// 	}
// 	HeapDestroy(&heap);
// 	return 0;
// }
// int main()
// {
// 	// printf("------------------\n");
// 	Heap heap;
// 	// printf("------------------\n");
// 	HeapInit(&heap);
// 	HeapPush(&heap, 3);
// 	HeapPush(&heap, 5);
// 	HeapPush(&heap, 6);
// 	HeapPush(&heap, 10);
// 	HeapPush(&heap, 3);

// 	for (int i = 0; i < (int)heap.szie; i++)
// 	{
// 		printf("%d ", heap.elem[i]);
// 	}
// 	return 0;
// }

// int main()
//{
//
//   //printf("%d",(0-1)/2);
//   return 0;
// }
