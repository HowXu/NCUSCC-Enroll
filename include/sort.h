#include "random.h"
//冒泡排序
int bubble_sort(union data *arr,int len,int type);
//基础堆排序
int heap_sort(union data *arr,int len,int type);
//斐波那契堆排序
// 以下内容基本全部使用chatgpt生成 T_T

// 斐波那契堆的节点
typedef struct FibHeapNode {
    union data key;
    int degree;
    struct FibHeapNode* parent;
    struct FibHeapNode* child;
    struct FibHeapNode* left;
    struct FibHeapNode* right;
    int mark;  // 标记节点是否失去子节点
} FibHeapNode;

// 斐波那契堆的结构
typedef struct FibHeap {
    FibHeapNode* min;  // 指向最小节点
    int n;             // 堆中节点的总数
} FibHeap;

// 创建新的斐波那契堆
FibHeap* createFibHeap();

// 创建新的斐波那契堆节点
FibHeapNode* createFibHeapNode(union data key);

// 合并两个斐波那契堆的根链表
void fibHeapLink(FibHeap* heap, FibHeapNode* y, FibHeapNode* x);

// 将一个节点插入到斐波那契堆
void fibHeapInsert(FibHeap* heap, FibHeapNode* node,int type);

// 提取最小值操作
FibHeapNode* fibHeapExtractMin(FibHeap* heap,int type);

// 合并堆的根链表，确保每个度数唯一
void fibHeapConsolidate(FibHeap* heap,int type);

// 斐波那契堆排序函数
void fibonacciHeapSort(union data *arr, int n,int type);

//到这里就没有了哈
// 交换值
void swap(union data *arr,int index_1,int index_2);

// 创建最大堆
void heapify(union data *arr,int len,int root,int type);