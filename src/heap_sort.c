#include "../include/sort.h"

// 基础堆排序
int heap_sort(union data *arr, int len, int type)
{
    // 数组转换为最大堆
    for (int i = len / 2 - 1; i >= 0; i--)
    {
        //对每个节点进行最大堆化
        heapify(arr, len, i, type);
    }

    //从屁股上面开始拿元素 len--确保已经被换到最末尾的数不会被重新堆化
    for (int i = len - 1; i >= 0; i--)
    {
        //交换堆顶
        swap(arr,i,0);
        //继续对剩下的部分进行堆化，依旧指定0为根节点
        heapify(arr,i,0,type);
    }
    
}

void heapify(union data *arr, int len, int root, int type)
{
    // 从root根节点计算调整为最大堆

    int largest = root;       // 初始化最大元素为根节点
    int left = 2 * root + 1;  // 左子节点的索引
    int right = 2 * root + 2; // 右子节点的索引
    switch (type)
    {
    case 0:
        // 如果左子节点大于根节点，将最大元素的索引设置为左子节点
        if (left < len && arr[left].i > arr[largest].i)
        {
            largest = left;
        }

        // 如果右子节点大于根节点，将最大元素的索引设置为右子节点
        if (right < len && arr[right].i > arr[largest].i)
        {
            largest = right;
        }

        // 如果最大元素不是根节点，将最大元素与根节点交换位置，并继续调整堆
        if (largest != root)
        {
            swap(arr, largest, root);
            heapify(arr, len, largest, type);
        }
        break;

    case 1:
        // 如果左子节点大于根节点，将最大元素的索引设置为左子节点
        if (left < len && arr[left].f > arr[largest].f)
        {
            largest = left;
        }

        // 如果右子节点大于根节点，将最大元素的索引设置为右子节点
        if (right < len && arr[right].f > arr[largest].f)
        {
            largest = right;
        }

        // 如果最大元素不是根节点，将最大元素与根节点交换位置，并继续调整堆
        if (largest != root)
        {
            swap(arr, largest, root);
            heapify(arr, len, largest, type);
        }
        break;
    }
}
