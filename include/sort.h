#include "random.h"
//冒泡排序
int bubble_sort(union data *arr,int len,int type);
//基础堆排序
int heap_sort(union data *arr,int len,int type);

void swap(union data *arr,int index_1,int index_2);

// 创建最大堆
void heapify(union data *arr,int len,int root,int type);