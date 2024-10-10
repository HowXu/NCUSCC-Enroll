#include "../../include/sort.h"
// #include <stdio.h>
/*
插入排序(InsertionSort)，一般也被称为直接插入排序。

对于少量元素的排序，它是一个有效的算法。插入排序是一种最简单的排序方法，它的基本思想是将一个记录插入到已经排好序的有序表中，从而一个新的、记录数增 1 的有序表

在其实现过程使用双层循环，外层循环对除了第一个元素之外的所有元素，内层循环对当前元素前面有序表进行待插入位置查找，并进行移动。

https://www.runoob.com/data-structures/insertion-sort.html

*/

// 从大到小

// 传入一个数组的指针 什么够吧语言不能获得数组长度
int insertion_sort(int *input, int len, int on)
{

    if (!on)
    {
        return 0;
    }
    // 获取数组长度

    // 为1拒绝
    if (len == 1)
    {
        printf("Len = 1\n");
        return -1;
    }

    int index_size = len - 1;
    for (int i = 0; i < index_size; i++)
    { // 这样就不会下标访问越界
        // 进行循环遍历 这里应该要保证索引i不会等于size 数组访问越界
        if (input[i + 1] > input[i])
        {
            // 后小于前 换位
            swap(input, i, i + 1);
            // 继续检查前面的值
            for (int d = i; d > 0; d--)
            {
                // 后小于前 换位 多次迭代调整所有值位置
                if (input[d] > input[d - 1])
                {
                    swap(input, d, d - 1);
                }
            }
        }
    }

    // 换完就ok了
    return 0;
}