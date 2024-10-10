#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "../include/sort.h"

// 创建新的斐波那契堆
FibHeap *createFibHeap()
{
    FibHeap *heap = (FibHeap *)malloc(sizeof(FibHeap));
    heap->min = NULL;
    heap->n = 0;
    return heap;
}

// 创建新的斐波那契堆节点
FibHeapNode *createFibHeapNode(union data key)
{
    FibHeapNode *node = (FibHeapNode *)malloc(sizeof(FibHeapNode));
    node->key = key;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    node->mark = 0;
    return node;
}

// 合并两个斐波那契堆的根链表
void fibHeapLink(FibHeap *heap, FibHeapNode *y, FibHeapNode *x)
{
    // 将y链接为x的子节点
    y->left->right = y->right;
    y->right->left = y->left;

    y->parent = x;

    if (x->child == NULL)
    {
        x->child = y;
        y->left = y->right = y;
    }
    else
    {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }

    x->degree++;
    y->mark = 0;
}

// 将一个节点插入到斐波那契堆
void fibHeapInsert(FibHeap *heap, FibHeapNode *node, int type)
{
    if (heap->min == NULL)
    {
        heap->min = node;
    }
    else
    {
        // 插入到最小节点旁边
        node->left = heap->min;
        node->right = heap->min->right;
        heap->min->right->left = node;
        heap->min->right = node;

        // 更新最小节点 这里的比较涉及switch
        switch (type)
        {
        case 0:
            if (node->key.i < heap->min->key.i)
            {
                heap->min = node;
            }
            break;

        case 1:
            if (node->key.f < heap->min->key.f)
            {
                heap->min = node;
            }
            break;
        }
    }
    heap->n++;
}

// 提取最小值操作
FibHeapNode *fibHeapExtractMin(FibHeap *heap,int type)
{
    FibHeapNode *z = heap->min;
    if (z != NULL)
    {
        // 将最小节点的每个子节点添加到根链表中
        if (z->child != NULL)
        {
            FibHeapNode *child = z->child;
            do
            {
                FibHeapNode *next = child->right;
                child->left = heap->min;
                child->right = heap->min->right;
                heap->min->right->left = child;
                heap->min->right = child;
                child = next;
            } while (child != z->child);
        }

        // 移除最小节点
        z->left->right = z->right;
        z->right->left = z->left;

        if (z == z->right)
        {
            heap->min = NULL;
        }
        else
        {
            heap->min = z->right;
            // 调整堆
            fibHeapConsolidate(heap,type); // 需要实现合并堆
        }
        heap->n--;
    }
    return z;
}

// 合并堆的根链表，确保每个度数唯一
void fibHeapConsolidate(FibHeap *heap, int type)
{
    int D = (int)(log(heap->n) / log(2)) + 1;
    //FibHeapNode *A[D];
    // 动态分配 A 数组 Windows的Mingw不支持c99
    FibHeapNode** A = (FibHeapNode**)malloc(D * sizeof(FibHeapNode*));
    //FibHeapNode *A = (FibHeapNode *) malloc(sizeof(FibHeapNode *[D]));

    for (int i = 0; i < D; i++)
    {
        A[i] = NULL;
    }

    FibHeapNode *x = heap->min;
    int numRoots = 0;
    if (x != NULL)
    {
        numRoots++;
        x = x->right;
        while (x != heap->min)
        {
            numRoots++;
            x = x->right;
        }
    }

    switch (type)
    {
    case 1:
        while (numRoots > 0)
        {
            int d = x->degree;
            FibHeapNode *next = x->right;

            while (A[d] != NULL)
            {
                FibHeapNode *y = A[d]; // y与x度数相同
                if (x->key.i > y->key.i)
                { // 交换x与y
                    FibHeapNode *temp = x;
                    x = y;
                    y = temp;
                }
                fibHeapLink(heap, y, x);
                A[d] = NULL;
                d++;
            }

            A[d] = x;
            x = next;
            numRoots--;
        }

        heap->min = NULL;

        for (int i = 0; i < D; i++)
        {
            if (A[i] != NULL)
            {
                if (heap->min == NULL)
                {
                    heap->min = A[i];
                    heap->min->left = heap->min;
                    heap->min->right = heap->min;
                }
                else
                {
                    A[i]->left = heap->min;
                    A[i]->right = heap->min->right;
                    heap->min->right->left = A[i];
                    heap->min->right = A[i];
                    if (A[i]->key.i < heap->min->key.i)
                    {
                        heap->min = A[i];
                    }
                }
            }
        }
        break;

    case 0:
        while (numRoots > 0) {
        int d = x->degree;
        FibHeapNode* next = x->right;

        while (A[d] != NULL) {
            FibHeapNode* y = A[d];  // y与x度数相同
            if (x->key.f > y->key.f) {  // 交换x与y
                FibHeapNode* temp = x;
                x = y;
                y = temp;
            }
            fibHeapLink(heap, y, x);
            A[d] = NULL;
            d++;
        }

        A[d] = x;
        x = next;
        numRoots--;
    }

    heap->min = NULL;

    for (int i = 0; i < D; i++) {
        if (A[i] != NULL) {
            if (heap->min == NULL) {
                heap->min = A[i];
                heap->min->left = heap->min;
                heap->min->right = heap->min;
            } else {
                A[i]->left = heap->min;
                A[i]->right = heap->min->right;
                heap->min->right->left = A[i];
                heap->min->right = A[i];
                if (A[i]->key.f < heap->min->key.f) {
                    heap->min = A[i];
                }
            }
        }
    }
        break;
    }
}

// 斐波那契堆排序函数
void fibonacciHeapSort(union data arr[], int n, int type)
{
    FibHeap *heap = createFibHeap();

    // 将所有元素插入斐波那契堆
    for (int i = 0; i < n; i++)
    {
        FibHeapNode *node = createFibHeapNode(arr[i]);
        fibHeapInsert(heap, node, type);
    }

    // 提取最小值，进行排序
    for (int i = 0; i < n; i++)
    {
        FibHeapNode *minNode = fibHeapExtractMin(heap,type);
        arr[i] = minNode->key; // 这里是直接进行指针访问赋值 因此排序无需返回值
        free(minNode);         // 释放节点
    }
}

/*
// 打印数组
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[] = {21, 7, 3, 12, 18, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: \n");
    printArray(arr, n);

    // 使用斐波那契堆进行排序
    fibonacciHeapSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);

    return 0;
}
*/
